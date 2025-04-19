#ifndef PARSE_H
#define PARSE_H

#include <memory>
#include <QJsonDocument>
#include <QSqlQuery>

#include "chartdata.hpp"

using namespace std;

class Parse
{
public:
    virtual shared_ptr<ChartData> parseSql(const QSqlDatabase& db) const = 0;
    virtual shared_ptr<ChartData> parseJson(const QJsonDocument& doc) const = 0;
    virtual ~Parse() = default;
};

class TimeValueDataParse : public Parse
{
public:
    virtual shared_ptr<ChartData> parseSql(const QSqlDatabase& db) const;
    virtual shared_ptr<ChartData> parseJson(const QJsonDocument& doc) const;
protected:

    /// methods for work with Sqlite
    TimeRecord getTimeRecord(const QVariant &vDate, const QVariant &vValue) const;
    int getRowCount(const QString &tableName) const;

    /// methods for work with Json
    bool isTimeRecord(const QJsonObject &tr) const;
    void setLabels(const QJsonObject &obj, shared_ptr<TimeValueData> &ts) const;
    QJsonArray getSeries(const QJsonObject &obj) const;
    TimeRecord getTimeRecord(const QJsonValue &jsonVal) const;
};

class XYDataParse
{
public:
    virtual shared_ptr<ChartData> parseSql(const QSqlDatabase& db) const;
    virtual shared_ptr<ChartData> parseJson(const QJsonDocument& doc) const;
};

#endif // PARSE_H
