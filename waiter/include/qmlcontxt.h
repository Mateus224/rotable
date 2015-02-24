#ifndef QMLCONTEXT_H
#define QMLCONTEXT_H
#include <QList>
#include <qqmlcontext.h>
#include "table.h"

class qmlContxt
{
public:

    qmlContxt();
    ~qmlContxt();
    void contxt(QQmlContext &ctxt);
    void initContxt(int NumberOfTables, bool newOrder);

    QList <table*>  tableNumber;
};

#endif // QMLCONTEXT_H
