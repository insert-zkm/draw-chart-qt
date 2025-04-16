#ifndef EXTRACTDATA_H
#define EXTRACTDATA_H

#include <QFileInfo>

#include "timeseries.hpp"

class IExtractData
{
public:
    virtual TimeSeries exec(const QFileInfo& file) = 0;
    virtual ~IExtractData() = default;
};


class JsonExtract : public IExtractData {
protected:
    bool isTimeRecord(const QJsonObject& tr) const;
    void setLabels(const QJsonObject& obj, TimeSeries& ts) const;
    QJsonArray getSeries(const QJsonObject& obj) const;
    TimeRecord getTimeRecord(const QJsonValue& jsonValue) const;

public:
    virtual TimeSeries exec(const QFileInfo& file) override;
};

class SqlExtract : public IExtractData {
protected:
    TimeRecord getTimeRecord(const QVariant& vDate, const QVariant& vValue) const;
    int getRowCount(const QString& tableName) const;
public:
    virtual TimeSeries exec(const QFileInfo& file) override;
};



#endif // EXTRACTDATA_H
