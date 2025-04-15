#include "extractdata.h"

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

bool JsonExtract::isTimeRecord(const QJsonObject &tr) const
{

    return tr.contains("time") && tr.contains("value"); // FIXME: hardcoded field names
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
    if(doc.isNull()) {
        qDebug() << "Error: json parse error" << parseError.errorString(); // FIXME
        return ts;
    }

    if(!doc.isArray()) {
        qDebug() << "Error: invalid json format" << "json document must be an array"; // FIXME
        return ts;
    }

    QJsonArray jsonTimeSeries = doc.array();
    for(auto it = jsonTimeSeries.cbegin(); it != jsonTimeSeries.cend(); it++) {
        if(it->isObject()) {
            QJsonObject obj = it->toObject();
            if(isTimeRecord(obj)){
                ts << TimeRecord();
            }
        }
    }


    return ts;
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
        qWarning() << "Warning: data in sqlite db";
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
    QString queryRowCountString = QString("SELECT Count(*) FROM %1").arg(tableName);
    QSqlQuery queryAllRecords(queryString);
    QSqlQuery queryRowCount(queryRowCountString);

    int rowCount = 0;
    bool ok = false;
    if(queryRowCount.next()) {
        int val = queryRowCount.value(0).toInt(&ok);
        rowCount = (ok ? val : 0); // FIXME
    }

    TimeSeries ts;
    ts.reserve(rowCount);


    while(queryAllRecords.next()) {
        QVariant vDateStr = queryAllRecords.value(col1);
        QVariant vValue = queryAllRecords.value(col2);

        if(!vDateStr.canConvert(QMetaType::QString) || !vValue.canConvert(QMetaType::QReal)) {
            qDebug() << "Error: wrong types"; // FIXME
        }

        QDateTime dt = QDateTime::fromString(vDateStr.toString(), "dd.MM.yyyy hh:mm");
        dt.setTimeSpec(Qt::UTC);

        if(!dt.isValid()) {
            qDebug() << "Error: invalid time format" << vDateStr.toString(); // FIXME
        }

        ts << TimeRecord(dt, vValue.toReal());
    }

    return ts;
}
