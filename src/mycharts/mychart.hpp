#ifndef MYCHART_H
#define MYCHART_H

#include <QAbstractSeries>

#include <memory>

#include "chartdata.hpp"

using namespace QtCharts;
using namespace std;

namespace MyCharts {
class Chart
{
public:
    virtual QAbstractSeries* create(shared_ptr<ChartData> data) const = 0;
};

class TimeValueChart : public Chart
{
public:
    virtual QAbstractSeries* create(shared_ptr<ChartData> data) const = 0;
};

class TimeValueLine : public TimeValueChart
{
public:
    virtual QAbstractSeries* create(shared_ptr<ChartData> data) const override;
};

class TimeValueHistogram : public TimeValueChart
{
public:
    virtual QAbstractSeries* create(shared_ptr<ChartData> data) const override;
};
}

#endif // MYCHART_H
