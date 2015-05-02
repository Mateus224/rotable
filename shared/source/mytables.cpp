#include "../include/mytables.h"
#include <QDebug>
#include <QObject>

myTables::myTables(QObject *parent) : QObject(parent)
{
}


//------------------------------------------------------------
QString myTables::tableNumber() const
{
    return m_tableNumber;
}

void myTables::settableNumber(const QString &tableNumber)
{
    if (tableNumber != m_tableNumber) {
        m_tableNumber = tableNumber;
        emit tableNumberChanged();
    }
}


//------------------------------------------------------------
void myTables::add_orderinformation(int m_pieces,QString m_orderName,float m_price,QString m_info_orderInfo)
{
    L_orderinformation.append(new OrderInformation( m_pieces, m_orderName, m_price, m_info_orderInfo));
}


//------------------------------------------------------------
void myTables::setColor_orderinformation(const int &position,const QString &color)
{
    OrderInformation* readyInformation;
    readyInformation=L_orderinformation.value(position);
    readyInformation->setinfo_orderInfo(color);
}


//------------------------------------------------------------
QString myTables::CallWaiter() const
{
    return m_CallWaiter;
}

void myTables::setCallWaiter(const QString &CallWaiter)
{
    if (CallWaiter != m_CallWaiter) {
        m_CallWaiter = CallWaiter;
        emit CallWaiterChanged();
    }
}


//------------------------------------------------------------
QString myTables::NewOrder() const
{
    return m_newOrder;
}

void myTables::setNewOrder(const QString &NewOrder)
{
    if (NewOrder != m_newOrder) {
        m_newOrder = NewOrder;
        emit NewOrderChanged();
    }
}


//------------------------------------------------------------
double myTables::toPay() const
{
    return m_toPay;
}

void myTables::setToPay(const double &toPay)
{
    if (toPay != m_toPay) {
        m_toPay = toPay;
        emit toPayChanged();
    }
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Get Information
//-----------------------------------------------------------------

//qml Slot
/*void myTables::add_or_removeProduct(int ProductID, bool add)
{
    if (add)
    {
        //addToProductHash(ProductID)
    }
    else
    {

    }
}*/

void myTables::addToProductHash(int id)
{
    //is this Product in the List? if not append if yes increase number
    if(ClientProductHash.contains(id))
    {
        Product=ClientProductHash.take(id);
        Product._s_quantity++;
        ClientProductHash.insert(Product._s_quantity,Product);

    }
    else
    {
        productChoosen* Product1=new productChoosen;
        Product1->_s_id=id;
        Product1->_s_quantity=1;
        ClientProductHash.insert(Product1->_s_quantity,*Product1);
    }

}
/*
void myTables::rmFromProductHash(int id)
{
    //is this product in the list? if one rm this from the list if more decrease it
}


void myTables::ProductHashManaging()
{

}
*/
