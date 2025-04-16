#include <QDebug>
#include "src/extractdata.h";

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

#include <QFileInfo>


int main() {
    IExtractData* st = new JsonExtract();
//    QFileInfo f("../draw-chart-qt/test/data/TEMPERATURE_NOVOSIB.sqlite");
    QFileInfo f("../draw-chart-qt/test/data/some.json");

    TimeSeries a = st->exec(f);

    for(auto it = a.begin(); it != a.end(); it++) {
        qDebug() << (*it);
    }

    delete st;

    return 0;
}
