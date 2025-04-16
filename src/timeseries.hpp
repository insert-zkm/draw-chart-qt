#ifndef TIMESERIES_H
#define TIMESERIES_H

#include <QDateTime>
#include <QPair>
#include <QList>
#include <QString>

typedef QPair<QDateTime, qreal> TimeRecord;

struct TimeSeries {
    QString xLabel;
    QString yLabel;
    QList<TimeRecord> data;
};

#endif // TIMESERIES_H
