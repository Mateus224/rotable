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
void myTables::add_orderinformation(QString m_order,int m_pieces,QString m_orderName,float m_price,QString m_ready,QString m_cancellation)
{
    L_orderinformation.append(new OrderInformation(m_order, m_pieces, m_orderName, m_price, m_ready, m_cancellation));
}


//------------------------------------------------------------
void myTables::cancellation_orderinformation(int position)
{
    OrderInformation* cancellationInformation;
    cancellationInformation=L_orderinformation.takeAt(position);
    cancellationInformation->setcancellation("red");
    L_orderinformation.insert(position,cancellationInformation);
}

void myTables::ready_orderinformation(int position)
{
    OrderInformation* readyInformation;
    readyInformation=L_orderinformation.takeAt(position);
    readyInformation->setready("green");
    L_orderinformation.insert(position,readyInformation);
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

