#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QObject>
#include <QFileInfo>
#include <QtCharts>
#include <QCheckBox>

#include <memory>

#include "includes/ComboBox/seperatorcombobox.hpp"
#include "includes/ioc_container.hpp"
#include "chartdata.hpp"


enum ChartType {
    TimeValueLine       = 0x00001,
    TimeValueHistogram  = 0x00002,
    TimeValuePie  = 0x00003,
    TimeValueMask       = 0x0000f,

    XYLine              = 0x00010,
    XYMask              = 0x000f0
};

using namespace std;

class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr);

    void fillComboBoxes();

public slots:
    void drawChart(const QFileInfo& fi);

    void activatedChartType(int index);

    void activatedGrayScale(int index);

    void reDrawChart();

    void print(bool checked = false);

signals:
    void printStatus(bool status);

protected:
    void changeContainerChartType(const ChartType &chtype);
    void changeContainerFileExtractor(const QString& fileType);


protected:
    QChart* ch;
    QChartView* cv;
    QGraphicsColorizeEffect* gce;

    QCheckBox* grayScaleTogler;
    SeparatorComboBox* chartTypeCB;
    unique_ptr<ioc::Container> container;
    shared_ptr<ChartData> data;
    void clearChart();
};

#endif // CHARTWIDGET_H
