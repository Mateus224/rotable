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



//--------------------------------------------------------
void qmlContxt::initContxt(int NumberOfTables)
{
    tab=new myTables();
    for(int i=0;i <NumberOfTables; i++)
    {
      tableNumber.append(new myTables());
      tableNumber.at(i)->setNewOrder("White");
    }
}


//--------------------------------------------------------
void qmlContxt::add_orderInfoForTable(int tableNr,int pices,QString OrderName, float price)
{
    tab=tableNumber.at(tableNr);
    tab->add_orderinformation("Red", pices,OrderName, price, false, false );
}


//--------------------------------------------------------
void qmlContxt::contxt(int tableNr)
{

    tab=tableNumber.at(tableNr);


    ctxt.setContextProperty("myModel", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tableNumber))));
    ctxt.setContextProperty("table", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tab->L_orderinformation))));
    ctxt.setContextProperty("con", this);
}


//--------------------------------------------------------
void qmlContxt::resetOldCurrentTable()
{
    for(int i=0;i<tableNumber.length();i++)
    {
        tableNumber.at(i)->settableNumber("Transparent");

    }
}


//--------------------------------------------------------
void qmlContxt::addAllPrices()
{
    double toPay=0;
    for(int i=0;i<tableNumber.at(m_tableNumber)->L_orderinformation.length();i++)
    {
         toPay+=tableNumber.at(m_tableNumber)->L_orderinformation.at(i)->m_price;
    }
    tableNumber.at(m_tableNumber)->setToPay(toPay);
    //qDebug()<<toPay;

}


//--------------------------------------------------------
void qmlContxt::holdNewOrder()
{
    for(int i=0;i<tableNumber.length();i++)
    {
        if(tableNumber.at(i)->NewOrder()!=("Red"))
        {
            tableNumber.at(i)->setNewOrder("White");
        }
        else
        {
            tableNumber.at(i)->setNewOrder("Red");
        }
    }
}


