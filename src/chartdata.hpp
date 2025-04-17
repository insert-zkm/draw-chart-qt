#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QDateTime>
#include <QPair>
#include <QList>
#include <QString>
#include <QPointF>

typedef QPair<QDateTime, qreal> TimeRecord;
typedef QPointF CoordRecord;

struct ChartData {
    QString xLabel;
    QString yLabel;
};

struct TimeValueData : public ChartData {
    QList<TimeRecord> data;
};

struct CoordsData : public ChartData {
    QList<TimeRecord> data;
};

#endif // CHARTDATA_H
