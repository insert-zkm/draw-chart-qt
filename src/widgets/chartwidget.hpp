#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QObject>
#include <QFileInfo>
#include <QtCharts>

#include <memory>

#include "includes/ComboBox/seperatorcombobox.hpp"
#include "includes/ioc_container.hpp"


enum ChartType {
    TimeValueLine       = 0x00001,
    TimeValueHistogram  = 0x00002,
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

    void activatedChartTheme(int index);

protected:
    void changeContainerChartType(const ChartType &chtype);
    void changeContainerFileExtractor(const QString& fileType);


protected:
    QChart* ch;
    QChartView* cv;

    SeparatorComboBox* chartTypeCB;
    SeparatorComboBox* styleCB;
    unique_ptr<ioc::Container> container;
    void clearChart();
};

#endif // CHARTWIDGET_H
