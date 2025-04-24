#include "mychart.hpp"
#include "qbarset.h"

#include <QLineSeries>
#include <QBarSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QDebug>
#include <QBarCategoryAxis>
#include <QScatterSeries>


#include <memory>

void MyCharts::TimeValueLine::create(shared_ptr<ChartData> data, QChart* ch) const
{
    QLineSeries* series = new QLineSeries();
    shared_ptr<TimeValueData> d = dynamic_pointer_cast<TimeValueData>(data);
    if(nullptr == d) {
        throw QString("Passed wrong derived class of ChartData");
    }

    data->sort();
    for(auto it = d->data.cbegin(); it != d->data.cend(); it++) {
        series->append(it->first.toMSecsSinceEpoch(), it->second);
    }

    ch->addSeries(series);

    QDateTimeAxis* dtAxis = new QDateTimeAxis();
    QValueAxis* valAxis = new QValueAxis();

    dtAxis->setTitleText(data->xLabel);
    valAxis->setTitleText(data->yLabel);

    ch->addAxis(dtAxis, Qt::AlignBottom);
    ch->addAxis(valAxis, Qt::AlignLeft);
    series->attachAxis(dtAxis);
    series->attachAxis(valAxis);
}

void MyCharts::TimeValueHistogram::create(shared_ptr<ChartData> data, QChart* ch) const
{
    const int barCount = 10;
    QBarSeries* series = new QBarSeries();

    shared_ptr<TimeValueData> d = dynamic_pointer_cast<TimeValueData>(data);
    if(nullptr == d) {
        throw QString("Passed wrong derived class of ChartData");
    }
    d->sort();

    QDateTime minVal, maxVal;
    if(!d->data.isEmpty()) {
        minVal = d->data[0].first;
        maxVal = d->data[0].first;
        if(d->data.size() >= 2) {
            maxVal = d->data.last().first;
        }
    }

    QDateTime border = minVal.addMonths(1);
    QStringList months;

    auto barSet = new QBarSet(minVal.toString("MMM yyyy"));
    for(int i = 0; i < d->data.size();) {
        int count = 0;
        months << QString::number(i + 1);
        for(;i < d->data.size() && d->data[i].first < border; i++) {
            count += 1;
        }

        *barSet << count;
        border = border.addMonths(1);
    }
    series->append(barSet);
    ch->addSeries(series);

    QBarCategoryAxis* dateAxis = new QBarCategoryAxis();
    dateAxis->append(months);
    QValueAxis* freqAxis = new QValueAxis();

    dateAxis->setTitleText(data->xLabel);
    freqAxis->setTitleText(data->yLabel);

    ch->addAxis(freqAxis, Qt::AlignLeft);
    ch->addAxis(dateAxis, Qt::AlignBottom);
    series->attachAxis(freqAxis);
    series->attachAxis(dateAxis);
}

void MyCharts::XYScatter::create(shared_ptr<ChartData> data, QChart *ch) const
{
    // FEATURE
}
