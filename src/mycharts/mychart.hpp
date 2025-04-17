#ifndef MYCHART_H
#define MYCHART_H

#include <QAbstractSeries>

#include <memory>

#include "chartdata.hpp"

using namespace QtCharts;
using namespace std;

class MyChart
{
public:
    virtual shared_ptr<QAbstractSeries> create(shared_ptr<ChartData> data) const = 0;
};

class TimeSeriesChart : public MyChart
{
public:
    virtual shared_ptr<QAbstractSeries> create(shared_ptr<ChartData> data) const = 0;
};

class TimeSeriesLine : public TimeSeriesChart
{
public:
    virtual shared_ptr<QAbstractSeries> create(shared_ptr<ChartData> data) const override;
};

class TimeSeriesHistogram : public TimeSeriesChart
{
public:
    virtual shared_ptr<QAbstractSeries> create(shared_ptr<ChartData> data) const override;
};

#endif // MYCHART_H
