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
    virtual bool isEmpty() const {
        return true;
    }
    virtual void sort() = 0;
    virtual void clear() {};
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

    virtual void clear() override {
        data.clear();
    }

    virtual bool isEmpty() const override {
        return data.isEmpty();
    }
};

class CoordsData : public ChartData {
public:
    QList<CoordRecord> data;

    virtual void sort() override {
        std::sort(data.begin(), data.end(), [](const CoordRecord& a, const CoordRecord& b) {
            return a.x() < b.x();
        });
    }

    virtual void clear() override {
        data.clear();
    }

    virtual bool isEmpty() const override {
        return data.isEmpty();
    }
};

#endif // CHARTDATA_H
