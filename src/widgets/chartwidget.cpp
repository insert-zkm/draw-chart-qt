#include "chartwidget.hpp"

#include <QComboBox>
#include <QGraphicsEffect>
#include <QPdfWriter>
#include <QFileDialog>

#include "parse.hpp"
#include "extractdata.hpp"
#include "mychart.hpp"

ChartWidget::ChartWidget(QWidget *parent)
    : QWidget(parent)
{
    container = unique_ptr<ioc::Container>(new ioc::Container());
    emit printStatus(true);

    chartTypeCB = new SeparatorComboBox();
    grayScaleTogler = new QCheckBox("gray scale");

    QHBoxLayout *l2 = new QHBoxLayout();
    l2->addWidget(chartTypeCB);
    l2->addWidget(grayScaleTogler);

    QVBoxLayout *l1 = new QVBoxLayout(this);
    l1->setContentsMargins(0, 0, 0, 0);
    l2->setContentsMargins(10, 10, 10, 0);

    ch = new QChart();
    cv = new QChartView(ch);

    gce = new QGraphicsColorizeEffect;
    gce->setColor(Qt::black);
    gce->setEnabled(false);
    ch->setGraphicsEffect(gce);
    ch->setBackgroundRoundness(0);

    l1->addLayout(l2);
    l1->addWidget(cv);

    fillComboBoxes();

    QObject::connect(chartTypeCB, QOverload<int>::of(&QComboBox::activated),
            this, &ChartWidget::activatedChartType);
    QObject::connect(chartTypeCB, QOverload<int>::of(&QComboBox::activated),
                     this, &ChartWidget::reDrawChart);
    QObject::connect(grayScaleTogler, &QCheckBox::stateChanged,
                     this, &ChartWidget::activatedGrayScale);
}

void ChartWidget::fillComboBoxes() {
    chartTypeCB->addParentItem("Time Series");
    chartTypeCB->addChildItem("Line chart", ChartType::TimeValueLine);
    chartTypeCB->addChildItem("Histogram chart", ChartType::TimeValueHistogram);
    chartTypeCB->addParentItem("XY Series");
    chartTypeCB->addChildItem("Line chart", ChartType::XYLine);

    chartTypeCB->setCurrentIndex(1);
    data = make_shared<TimeValueData>();
    container->registerInstance<Parse, TimeValueDataParse>();
    container->registerInstance<MyCharts::Chart, MyCharts::TimeValueLine>();


    {
        // hack to disable combo box item
        QModelIndex idx = chartTypeCB->model()->index(4, 0);

        QVariant v(0);
        chartTypeCB->model()->setData(idx, v, Qt::UserRole -1);
    }
}

void ChartWidget::drawChart(const QFileInfo &fi) {
    changeContainerFileExtractor(fi.suffix());

    shared_ptr<ExtractData> extractor = container->resolve<ExtractData>();
    shared_ptr<MyCharts::Chart> seriesCreator = container->resolve<MyCharts::Chart>();

    try {
        data = extractor->exec(fi);
        emit printStatus(false);
    } catch(const QString& e) {
        QMessageBox::critical(this,
                              "Error",
                              e);
        clearChart();
        data->clear();
        emit printStatus(true);
        return;
    }

    clearChart();
    seriesCreator->create(data, ch);
}

void ChartWidget::reDrawChart() {
    if(!data.get() || data->isEmpty()) {
        return;
    }
    shared_ptr<MyCharts::Chart> seriesCreator = container->resolve<MyCharts::Chart>();

    clearChart();
    emit printStatus(false);
    seriesCreator->create(data, ch);
}

void ChartWidget::print(bool checked)
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save the file as PDF"),
                                                    QDir::currentPath(),
                                                    tr("(PDF Files)*.pdf"));

    if (fileName.isEmpty()) {
        return;
    }
    QPdfWriter writer(fileName);
    writer.setPageSize(QPagedPaintDevice::A4);
    QPainter painter(&writer);
    cv->render(&painter);
    painter.end();
}

void ChartWidget::activatedChartType(int index) {
    ChartType type = static_cast<ChartType>(chartTypeCB->itemData(index).toInt());
    changeContainerChartType(type);
}

void ChartWidget::activatedGrayScale(int state)  {
    gce->setEnabled(Qt::Checked == state);
}

void ChartWidget::changeContainerChartType(const ChartType& chtype) {
    if (chtype & ChartType::TimeValueMask) {
        container->registerInstance<Parse, TimeValueDataParse>();
        if (ChartType::TimeValueLine == chtype) {
            container->registerInstance<MyCharts::Chart, MyCharts::TimeValueLine>();
        } else if (ChartType::TimeValueHistogram == chtype) {
            container->registerInstance<MyCharts::Chart, MyCharts::TimeValueHistogram>();
        } else {
            qWarning() << "ChartType is not registered under ChartType::TimeValueMask";
        }

    } else if (chtype & ChartType::XYMask) {
        // FEATURE
    }

}

void ChartWidget::changeContainerFileExtractor(const QString &fileType)
{
    if("sqlite" == fileType) {
        container->registerFactory<ExtractData, SqlExtract, Parse>();
    } else if ("json" == fileType) {
        container->registerFactory<ExtractData, JsonExtract, Parse>();
    } else {
        qWarning() << "Unknown file type";
    }
}

void ChartWidget::clearChart() {
    ch->removeAllSeries();
    auto axis = ch->axes();
    for(auto it = axis.begin(); it != axis.end(); it++) {
        ch->removeAxis((*it));
    }
}
