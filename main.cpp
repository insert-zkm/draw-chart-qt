#include <QDebug>
#include "extractdata.hpp";

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

#include <QFileInfo>


int main() {
    QVariant v(99999999999999);
    bool ok;
    qDebug() << v << v.canConvert(QMetaType::Int) << v.toUInt(&ok);

    qDebug() << ok;

    return 0;

    IExtractData* st = new JsonExtract();
//    QFileInfo f("../draw-chart-qt/test/data/TEMPERATURE_NOVOSIB.sqlite");
    QFileInfo f("../draw-chart-qt/test/data/some.json");

    TimeSeries a = st->exec(f);
//    qDebug() << "ts: " << &a << " ts.data: " << &(a.data);

    for(auto it = a.data.begin(); it != a.data.end(); it++) {
//        qDebug() << (*it);
    }

    delete st;

    return 0;
}
