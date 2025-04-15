#ifndef EXTRACTDATA_H
#define EXTRACTDATA_H

#include <QList>
#include <QPair>
#include <QDateTime>
#include <QFileInfo>

typedef QPair<QDateTime, qreal> TimeRecord;
typedef QList<TimeRecord> TimeSeries;


class IExtractData
{
public:
    virtual TimeSeries exec(const QFileInfo& file) = 0;
};


class JsonExtract : public IExtractData {
protected:
    bool isTimeRecord(const QJsonObject& tr) const;

public:
    virtual TimeSeries exec(const QFileInfo& file) override;
};

class SqlExtract : public IExtractData {
public:
    virtual TimeSeries exec(const QFileInfo& file) override;
};



#endif // EXTRACTDATA_H
