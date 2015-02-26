#include "qmlcontxt.h"
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QtQuick>



//qmlContxt::qmlContxt(QObject *parent): QObject(parent)
//{

//}

qmlContxt::qmlContxt(QQmlContext &qmlCon, QObject *parent) :QObject(parent), ctxt(qmlCon)
{
    //QList<myTables*> tableNumber=;

}


void qmlContxt::initContxt(int NumberOfTables, bool newOrder)
{
    for(int i=0;i <NumberOfTables; i++)
    {
      tableNumber.append(new myTables());
    }
    tab->settableNumber(NumberOfTables);
}


void qmlContxt::add_orderInfoForTable(int tableNr )
{
    tab=new myTables();
    tab=tableNumber.at(tableNr);
    tab->add_orderinformation( "RED", 3, "Sambuca", 2, false, false );
    tab->add_orderinformation( "blue", 3, "Vodka", 2, false, false );
    tab->add_orderinformation( "Nie", 2, "Vodka", 3, true, false );
}

void qmlContxt::contxt(int tableNr)
{

    //tab=tableNumber.at(tableNr);

    ctxt.setContextProperty("con", this);
    ctxt.setContextProperty("myModel", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tab->L_orderinformation))));
    ctxt.setContextProperty("table", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tab->L_orderinformation))));

}

