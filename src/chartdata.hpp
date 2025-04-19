#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QDateTime>
#include <QPair>
#include <QList>
#include <QString>
#include <QPointF>
#include <algorithm>

typedef QPair<QDateTime, qreal> TimeRecord;
typedef QPointF CoordRecord;

class ChartData {
public:
    QString xLabel;
    QString yLabel;
    virtual void sort() = 0;
    virtual ~ChartData() = default;
};

class TimeValueData : public ChartData {
public:
    QList<TimeRecord> data;
    virtual void sort() override {
        std::sort(data.begin(), data.end(), [](const TimeRecord& a, const TimeRecord& b) {
            return a.first < b.first;
        });
    }
};

class CoordsData : public ChartData {
public:
    QList<CoordRecord> data;
};

#endif // CHARTDATA_H
