#include "win.hpp"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QAbstractSeries>
#include <QStringListModel>
#include <QVariant>

Win::Win(QWidget *parent)
    : QWidget(parent)
{
    dataTypeCB = new QComboBox(this);
    fillComboBoxes();

}

void Win::fillComboBoxes() {
    QVector<QPair<QString, QString>> sl = {
        {"Line chart", "l"},
        {"Historgram chart", "h"}
    };
    dataTypeCB->addItem("Временные ряды", sl);
    dataTypeCB->addItem("(x, y) ряды", );
}
