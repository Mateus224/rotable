#include "qmlcontxt.h"
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QtQuick>


qmlContxt::qmlContxt(QQmlContext &qmlCon, QObject *parent) :QObject(parent), ctxt(qmlCon)
{
    m_tableNumber=0;
    AppWindow=new WaiterAppWindow;

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
    tab->add_orderinformation(pices,OrderName, price, "black");
}


//--------------------------------------------------------
void qmlContxt::contxt(int tableNr)
{

    tab=tableNumber.at(tableNr);


    ctxt.setContextProperty("myModel", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tableNumber))));
    ctxt.setContextProperty("table", QVariant::fromValue(*reinterpret_cast<QList<QObject*> *>(&(tab->L_orderinformation))));
    ctxt.setContextProperty("con", this);
    ctxt.setContextProperty("waiterAppWindows",AppWindow); 
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
        for(int j=0;j<tableNumber.at(m_tableNumber)->L_orderinformation.length();j++)
        {
             toPay+=tableNumber.at(m_tableNumber)->L_orderinformation.at(j)->m_price;
        }
    AppWindow->setToPay(toPay);
}


//--------------------------------------------------------
void qmlContxt::holdNewOrder()
{
    for(int i=0;i<tableNumber.length();i++)
    {
        if(tableNumber.at(i)->NewOrder()!=("red"))
        {
            tableNumber.at(i)->setNewOrder("white");
        }
        else
        {
            tableNumber.at(i)->setNewOrder("red");
        }
    }
}


