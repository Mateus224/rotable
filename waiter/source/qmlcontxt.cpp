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


}


void qmlContxt::initContxt(int NumberOfTables)
{
    tab=new myTables();
    for(int i=0;i <NumberOfTables; i++)
    {
      tableNumber.append(new myTables());
      tableNumber.at(i)->setNewOrder("Transparent");
    }
}


void qmlContxt::add_orderInfoForTable(int tableNr,int pices,QString OrderName, float price)
{
    tab=tableNumber.at(tableNr);
    tab->add_orderinformation("Red", pices,OrderName, price, false, false );
}

void qmlContxt::contxt(int tableNr)
{

    tab=tableNumber.at(tableNr);


    ctxt.setContextProperty("myModel", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tableNumber))));
    ctxt.setContextProperty("table", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tab->L_orderinformation))));
    ctxt.setContextProperty("con", this);
}

void qmlContxt::resetOldCurrentTable()
{
    for(int i=0;i<tableNumber.length();i++)
    {
        tableNumber.at(i)->settableNumber("Transparent");
    }
}


