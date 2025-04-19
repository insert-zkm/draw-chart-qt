#include "chartwidget.hpp"

#include <QComboBox>
#include <QGraphicsEffect>

#include "parse.hpp"
#include "chartdata.hpp"
#include "extractdata.hpp"
#include "mychart.hpp"

ChartWidget::ChartWidget(QWidget *parent)
    : QWidget(parent)
{
    container = unique_ptr<ioc::Container>(new ioc::Container());

    chartTypeCB = new SeparatorComboBox();
    styleCB = new SeparatorComboBox();

    QHBoxLayout *l2 = new QHBoxLayout();
    l2->addWidget(chartTypeCB);
    l2->addWidget(styleCB);

    QVBoxLayout *l1 = new QVBoxLayout(this);
    l1->setContentsMargins(0, 0, 0, 0);
    l2->setContentsMargins(10, 10, 10, 10);

    ch = new QChart();
    cv = new QChartView(ch);

    QGraphicsColorizeEffect *graphicsEffect = new QGraphicsColorizeEffect;
    graphicsEffect->setColor(Qt::black);
    graphicsEffect->setEnabled(false);
    ch->setGraphicsEffect(graphicsEffect);

    l1->addLayout(l2);
    l1->addWidget(cv);

    fillComboBoxes();

    QObject::connect(chartTypeCB, QOverload<int>::of(&QComboBox::activated),
            this, &ChartWidget::activatedChartType);
    QObject::connect(styleCB, QOverload<int>::of(&QComboBox::activated),
                     this, &ChartWidget::activatedChartTheme);
}

void ChartWidget::fillComboBoxes() {
    chartTypeCB->addParentItem("Time Series");
    chartTypeCB->addChildItem("Line chart", ChartType::TimeValueLine);
    chartTypeCB->addChildItem("Histogram chart", ChartType::TimeValueHistogram);
    chartTypeCB->addSeparator();
    chartTypeCB->addParentItem("XY Series");
    chartTypeCB->addChildItem("Line chart", ChartType::XYLine);

    chartTypeCB->setCurrentIndex(1);
    container->registerInstance<Parse, TimeValueDataParse>();
    container->registerInstance<MyCharts::Chart, MyCharts::TimeValueLine>();

    styleCB->addItem("light", QChart::ChartThemeLight);
    styleCB->addItem("dark", QChart::ChartThemeDark);
    styleCB->addItem("HighContrast", QChart::ChartThemeHighContrast);
}

void ChartWidget::drawChart(const QFileInfo &fi) {
    changeContainerFileExtractor(fi.suffix());

    shared_ptr<ExtractData> extractor = container->resolve<ExtractData>();
    shared_ptr<MyCharts::Chart> seriesCreator = container->resolve<MyCharts::Chart>();

    shared_ptr<ChartData> data;
    try {
        data = extractor->exec(fi);
    } catch(const exception& e) {
        qDebug() << e.what();
    } catch(const QString& e) {
        QMessageBox::critical(this,
                              "Error",
                              e);
        clearChart();
        return;
    }

    clearChart();
    QAbstractSeries* chartSeries = seriesCreator->create(data, ch);
}

void ChartWidget::activatedChartType(int index) {
    ChartType type = static_cast<ChartType>(chartTypeCB->itemData(index).toInt());
    changeContainerChartType(type);
}

void ChartWidget::activatedChartTheme(int index)  {
//    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(chartTypeCB->itemData(index).toInt());
//    cv->chart()->setTheme(theme);
    cv->chart()->graphicsEffect()->setEnabled(true);
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
