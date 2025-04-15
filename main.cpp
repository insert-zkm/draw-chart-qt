#include <QDebug>
#include "src/extractdata.h";

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

#include <QFileInfo>


int main() {
    IExtractData* st = new SqlExtract();
    QFileInfo f("../draw-chart-qt/test/data/TEMPERATURE_NOVOSIB.sqlite");

    TimeSeries a = st->exec(f);

    for(auto it = a.begin(); it != a.end(); it++) {
        qDebug() << (*it);
    }

    return 0;
}
