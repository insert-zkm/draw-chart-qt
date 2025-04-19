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
    virtual ~ExtractData() {};
};


class JsonExtract : public ExtractData {
public:
    JsonExtract(shared_ptr<Parse> p) : ExtractData(p) {}
    virtual shared_ptr<ChartData> exec(const QFileInfo& file) const override;
};

class SqlExtract : public ExtractData {

public:
    SqlExtract(shared_ptr<Parse> p) : ExtractData(p) {}
    virtual shared_ptr<ChartData> exec(const QFileInfo& file) const override;
};



#endif // EXTRACTDATA_H
