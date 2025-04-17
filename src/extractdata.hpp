#ifndef EXTRACTDATA_H
#define EXTRACTDATA_H

#include <QFileInfo>
#include <memory>

#include "chartdata.hpp"
#include "parse.hpp"

using namespace std;

class ExtractData
{
protected:
    shared_ptr<Parse> _p;
public:
    ExtractData(shared_ptr<Parse> p) : _p(p) {}
    virtual shared_ptr<ChartData> exec(const QFileInfo& file) const = 0;
    virtual ~ExtractData() = default;
};


class JsonExtract : public ExtractData {
protected:
    bool isTimeRecord(const QJsonObject& tr) const;
    void setLabels(const QJsonObject& obj, shared_ptr<ChartData>& ts) const;
    QJsonArray getSeries(const QJsonObject& obj) const;
    TimeRecord getTimeRecord(const QJsonValue& jsonValue) const;

public:
    JsonExtract(shared_ptr<Parse> p) : ExtractData(p) {}
    virtual shared_ptr<ChartData> exec(const QFileInfo& file) const override;
};

class SqlExtract : public ExtractData {
protected:
    TimeRecord getTimeRecord(const QVariant& vDate, const QVariant& vValue) const;
    int getRowCount(const QString& tableName) const;
public:
    SqlExtract(shared_ptr<Parse> p) : ExtractData(p) {}
    virtual shared_ptr<ChartData> exec(const QFileInfo& file) const override;
};



#endif // EXTRACTDATA_H
