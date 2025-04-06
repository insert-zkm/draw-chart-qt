#ifndef EXTRACTDATA_H
#define EXTRACTDATA_H

#include <QList>
#include <QPair>
#include <QPoint>


typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;


class IExtractData
{
public:
    virtual DataTable exec(const QString& file_path) = 0;
};


class JsonExtract : public IExtractData {
public:
    virtual DataTable exec(const QString& file_path) override;
};

class DatExtract : public IExtractData {
public:
    virtual DataTable exec(const QString& file_path) override;
};

class SqlExtract : public IExtractData {
public:
    virtual DataTable exec(const QString& file_path) override;
};



#endif // EXTRACTDATA_H
