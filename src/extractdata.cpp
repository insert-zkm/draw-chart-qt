#include "extractdata.hpp"

#include <QSqlDatabase>
#include <QSqlError>

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonParseError>


#include <QDebug>
#include <QVariant>

shared_ptr<ChartData> JsonExtract::exec(const QFileInfo& file) const
{
    QFile f(file.absoluteFilePath());
    if(!f.open(QFile::ReadOnly)) {
        throw QString("Cannot open JSON file");
    }

    QByteArray s = f.readAll();
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(s, &parseError);
    if(doc.isNull() || parseError.error != QJsonParseError::NoError) {
        throw QString("JSON parse error " + parseError.errorString());
    }

    return _p->parseJson(doc);
}


shared_ptr<ChartData> SqlExtract::exec(const QFileInfo& file) const
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(file.absoluteFilePath());
    db.setConnectOptions("QSQLITE_OPEN_READONLY");

    if(!db.open()) {
        throw QString("Cannot open SQLITE file: " + db.lastError().text());
    }
    auto res = _p->parseSql(db);
    db.close();

    return res;
}
