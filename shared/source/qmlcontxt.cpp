#include "qmlcontxt.h"
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include "../../waiter/include/waiterappwindow.h"
//#include <QtQuick>


qmlContxt::qmlContxt(QQmlContext &qmlCon, QObject *parent) :QObject(parent), ctxt(qmlCon)
{
    m_tableNumber=0;
    //AppWindow=new WaiterAppWindow;

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
    //ctxt.setContextProperty("waiterAppWindows",AppWindow);
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
        for(int j=0;j<tableNumber.value(m_tableNumber)->L_orderinformation.length();j++)
        {
             toPay+=tableNumber.value(m_tableNumber)->L_orderinformation.at(j)->m_price;
        }
    //AppWindow->setToPay(toPay);
}


//--------------------------------------------------------
void qmlContxt::holdNewOrder()
{
    for(int i=0;i<tableNumber.length();i++)
    {
        if(tableNumber.value(i)->NewOrder()!=("red"))
        {
            tableNumber.value(i)->setNewOrder("white");
        }
        else
        {
            tableNumber.value(i)->setNewOrder("red");
        }
    }
}

//--------------------------------------------------------
//SLOTS
//--------------------------------------------------------

void qmlContxt::tableSlot(const int &msg) {

    m_tableNumber=msg-1;
    resetOldCurrentTable();
    tableNumber.at(m_tableNumber)->setCallWaiter("Black");
    tableNumber.at(m_tableNumber)->setNewOrder("Transparent");
    contxt(m_tableNumber);
    tableNumber.at(m_tableNumber)->settableNumber("Lightblue");
    addAllPrices();
    holdNewOrder();
}
//--------------------------------------------------------


void qmlContxt::readySlot(const QString &ready, const int &index)
{
    if(ready=="black")
    {
        tableNumber.value(m_tableNumber)->setColor_orderinformation(index, "green");
    }
    else if(ready=="green")
    {
        tableNumber.value(m_tableNumber)->setColor_orderinformation(index, "black");
    }
}
//--------------------------------------------------------


void qmlContxt::payedSlot()
{
    tableNumber.value(m_tableNumber)->L_orderinformation.clear();
    contxt(m_tableNumber);
}
//--------------------------------------------------------


void qmlContxt::cancSlot(const QString &canc, const int index)
{
    if(canc=="black")
    {
        tableNumber.value(m_tableNumber)->setColor_orderinformation(index, "red");
        s_storno_prices thisPrice= {tableNumber.value(m_tableNumber)->L_orderinformation.value(index)->m_price,index};
        L_price.append(thisPrice);
        tableNumber.value(m_tableNumber)->L_orderinformation.value(index)->setprice(0);
        addAllPrices();
    }
    else if(canc=="red")
    {
        tableNumber.value(m_tableNumber)->setColor_orderinformation(index, "black");
        for(int i=0; i<L_price.length();i++)
        {
           if (L_price.value(i).s_index==index)
           {
               tableNumber.value(m_tableNumber)->L_orderinformation.value(index)->setprice(L_price.value(i).s_price );
               addAllPrices();
           }
        }
    }
}

//--------------------------------------------------------



