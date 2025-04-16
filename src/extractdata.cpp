#include "extractdata.hpp"

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>
#include <QVariant>

#define DEFAULT_XLABEL "time"
#define DEFAULT_YLABEL "value"

bool JsonExtract::isTimeRecord(const QJsonObject &tr) const
{
    return tr.contains("time") && tr.contains("value"); // FIXME: hardcoded field names
}

void JsonExtract::setLabels(const QJsonObject &obj, TimeSeries &ts) const
{
    QJsonValue jXLabel = obj.value("xLabel");
    QJsonValue jYLabel = obj.value("yLabel");

    ts.xLabel = jXLabel.toString(QString(DEFAULT_XLABEL));
    ts.yLabel = jYLabel.toString(QString(DEFAULT_YLABEL));
}

QJsonArray JsonExtract::getSeries(const QJsonObject &obj) const
{
    if(!obj.contains("series")) {
        qDebug() << "Warning: no series field in object. By default its gonna be empty array";
    }
    QJsonValue jSeries = obj.value("series");
    if(!jSeries.isArray()) {
        qDebug() << "Error: invalid json format" << "series must be an array"; // FIXME
    }

    return jSeries.toArray();
}

TimeRecord JsonExtract::getTimeRecord(const QJsonValue &jsonVal) const
{
    if(!jsonVal.isObject()) {
        qWarning() << "Warning: invalid json array element must be object"; // FIXME
        return TimeRecord();
    }

    QJsonObject obj = jsonVal.toObject();
    if(!isTimeRecord(obj)){
        qWarning() << "Warning: invalid json object must contain 'time' and 'value' fields"; // FIXME
        return TimeRecord();
    }

    QJsonValue jTime = obj.value("time");
    QJsonValue jValue = obj.value("value");

    bool ok;
    QString epochTimeStr = jTime.toString();
    qint64 epochTime = epochTimeStr.toULongLong(&ok);
    qreal value = jValue.toDouble();

    if(!ok) {
        qWarning() << "Warning: invalid json convertion epoch time"; // FIXME
        return TimeRecord();
    }

    return TimeRecord(QDateTime::fromSecsSinceEpoch(epochTime), value);
}



TimeSeries JsonExtract::exec(const QFileInfo& file)
{
    QFile f(file.absoluteFilePath());
    if(!f.open(QFile::ReadOnly)) {
        qDebug() << "Error: cannot open json file"; // FIXME
    }
    TimeSeries ts;
    QByteArray s = f.readAll();
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(s, &parseError);
    if(doc.isNull() || parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error: json parse error" << parseError.errorString(); // FIXME
        return ts;
    }

    if(!doc.isObject()) {
        qDebug() << "Error: invalid json format" << "json document must be an object"; // FIXME
        return ts;
    }

    QJsonObject rootObj = doc.object();
    QJsonArray jsonTimeSeries = getSeries(rootObj);
    setLabels(rootObj, ts);

    for(auto it = jsonTimeSeries.cbegin(); it != jsonTimeSeries.cend(); it++) {
        ts.data << getTimeRecord((*it));
    }
//    qDebug() << "ts: " << &ts << " ts.data: " << &(ts.data);
    return ts;
}

TimeRecord SqlExtract::getTimeRecord(const QVariant &vDate, const QVariant &vValue) const
{
    if(!vDate.canConvert(QMetaType::QString) || !vValue.canConvert(QMetaType::QReal)) {
        qDebug() << "Error: wrong types"; // FIXME
    }

    QDateTime dt = QDateTime::fromString(vDate.toString(), "dd.MM.yyyy hh:mm");
    dt.setTimeSpec(Qt::UTC);

    if(!dt.isValid()) {
        qDebug() << "Error: invalid datetime format" << vDate.toString(); // FIXME
    }

    return TimeRecord(dt, vValue.toReal());
}

int SqlExtract::getRowCount(const QString &tableName) const
{
    QSqlQuery queryRowCount(
        QString("SELECT Count(*) FROM %1").arg(tableName));

    int rowCount = 0;
    bool ok = false;
    if(queryRowCount.next()) {
        int val = queryRowCount.value(0).toInt(&ok);
        rowCount = (ok ? val : 0); // FIXME
    }
    return rowCount;
}

TimeSeries SqlExtract::exec(const QFileInfo& file)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(file.absoluteFilePath());
    db.setConnectOptions("QSQLITE_OPEN_READONLY");

    if(!db.open()) {
        qDebug() << "Error: cannot open sqlite file" << db.lastError().text(); // FIXME
    }

    QStringList tables = db.tables();
    if(tables.isEmpty()) {
        qWarning() << "Warning: no tables in sqlite db";
        return TimeSeries();
    }
    QString tableName = tables.first();
    QSqlRecord record = db.record(tableName);

    if(record.count() < 2) {
        qDebug() << "Error: not enough info to build a graph"; // FIXME
    }

    QString col1 = record.fieldName(0), col2 = record.fieldName(1);
    QString queryString = QString("SELECT %1, %2 FROM %3")
                              .arg(col1)
                              .arg(col2)
                              .arg(tableName);
    QSqlQuery queryAllRecords(queryString);

    int rowCount = getRowCount(tableName);
    TimeSeries ts;
    ts.data.reserve(rowCount);
    ts.xLabel = col1;
    ts.yLabel = col2;

    try {
        while(queryAllRecords.next()) {
            ts.data << getTimeRecord(
                queryAllRecords.value(col1),
                queryAllRecords.value(col2));
        }
    } catch(std::bad_alloc& baError) {
        qWarning() << "Warning: too much data. List bad allocation";
    }

    return ts;
}
