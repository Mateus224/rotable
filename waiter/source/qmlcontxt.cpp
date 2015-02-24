#include "qmlcontxt.h"
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QtQuick>

qmlContxt::qmlContxt()
{

}

qmlContxt::~qmlContxt()
{

}

void qmlContxt::initContxt(int NumberOfTables, bool newOrder)
{
    for(int i=0;i <NumberOfTables; i++)
    {
      tableNumber.append(new table(NumberOfTables, newOrder ));
    }
}


void qmlContxt::contxt(QQmlContext &ctxt)
{



    table* tab=new table;

    tab=tableNumber.at(3);
    tab->add_orderinformation("Table 1", "Hallo", 3, "Sambuca", 2, false, false );
    tab->add_orderinformation("Table 2", "Hallo", 3, "Vodka", 2, false, false );
    tab->add_orderinformation("Table 3", "Nie", 2, "Vodka", 3, true, false );



    ctxt.setContextProperty("con", tab);
    ctxt.setContextProperty("myModel", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tab->L_orderinformation))));
    ctxt.setContextProperty("table", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tab->L_orderinformation))));

}
