#include "../include/mytables.h"
#include <QDebug>
#include <QObject>

myTables::myTables(QObject *parent) : QObject(parent)
{
}


//------------------------------------------------------------
int myTables::tableNumber() const
{
    return m_tableNumber;
}

void myTables::settableNumber(const int &tableNumber)
{
    if (tableNumber != m_tableNumber) {
        m_tableNumber = tableNumber;
        emit tableNumberChanged();
    }
}


//------------------------------------------------------------
void myTables::add_orderinformation(QString m_order,int m_pieces,QString m_orderName,float m_price,bool m_ready,bool m_cancellation)
{
    L_orderinformation.append(new OrderInformation(m_order, m_pieces, m_orderName, m_price, m_ready, m_cancellation));
}


//------------------------------------------------------------
void myTables::cancellation_orderinformation(int position)
{
    OrderInformation* cancellationInformation;
    cancellationInformation=L_orderinformation.takeAt(position);
    cancellationInformation->setcancellation(true);
    L_orderinformation.insert(position,cancellationInformation);
}

void myTables::ready_orderinformation(int position)
{
    OrderInformation* readyInformation;
    readyInformation=L_orderinformation.takeAt(position);
    readyInformation->setready(true);
    L_orderinformation.insert(position,readyInformation);
}

