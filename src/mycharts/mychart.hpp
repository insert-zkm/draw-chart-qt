#ifndef MYCHART_H
#define MYCHART_H

#include <QAbstractSeries>
#include <QChart>

#include <memory>

#include "chartdata.hpp"

using namespace QtCharts;
using namespace std;

namespace MyCharts {
class Chart
{
public:
    virtual void create(shared_ptr<ChartData> data, QChart* ch) const = 0;
    virtual ~Chart() = default;
};

class TimeValueChart : public Chart
{
public:
    virtual void create(shared_ptr<ChartData> data, QChart* ch) const = 0;
    virtual ~TimeValueChart() = default;
};

class TimeValueLine : public TimeValueChart
{
public:
    virtual void create(shared_ptr<ChartData> data, QChart* ch) const override;
};

class TimeValueHistogram : public TimeValueChart
{
public:
    virtual void create(shared_ptr<ChartData> data, QChart* ch) const override;
};

class TimeValuePie : public TimeValueChart
{
public:
    virtual void create(shared_ptr<ChartData> data, QChart* ch) const override;
};

class XYChart : public Chart
{
public:
    virtual void create(shared_ptr<ChartData> data, QChart* ch) const = 0;
    ~XYChart() = default;
};

class XYScatter : public XYChart
{
public:
    virtual void create(shared_ptr<ChartData> data, QChart* ch) const;
};



}

#endif // MYCHART_H
