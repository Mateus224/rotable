#include <QDebug>
#include "../include/table.h"
#include <QObject>

table::table(QObject *parent) : QObject(parent)
{
}

table::table(const int &tableNumber, const QString &name, const QString &order,
             const int &pieces,const QString &orderName,
             const float &price,
             const bool &ready, const bool &cancellation,
             QObject *parent)
    : QObject(parent), m_tableNumber(tableNumber), m_name(name), m_order(order), m_pieces(pieces), m_orderName(orderName), m_price(price), m_ready(ready),m_cancellation(cancellation)
{
}


//------------------------------------------------------------
int table::tableNumber() const
{
    return m_tableNumber;
}

void table::settableNumber(const int &tableNumber)
{
    if (tableNumber != m_tableNumber) {
        m_tableNumber = tableNumber;
        emit tableNumberChanged();
    }
}


//------------------------------------------------------------
void table::add_orderinformation(QString m_name, QString m_order,int m_pieces,QString m_orderName,float m_price,bool m_ready,bool m_cancellation)
{
    L_orderinformation.append(new OrderInformation(m_name, m_order, m_pieces, m_orderName, m_price, m_ready, m_cancellation));
}

void table::cancellation_orderinformation(int position)
{
    QObject* cancellationInformation;
    cancellationInformation=L_orderinformation.takeAt(position);
    ((OrderInformation *)cancellationInformation)->setcancellation(true);
    L_orderinformation.insert(position,cancellationInformation);
}

void table::ready_orderinformation(int position)
{
    QObject* readyInformation;
    readyInformation=L_orderinformation.takeAt(position);
    ((OrderInformation *)readyInformation)->setready(true);
    L_orderinformation.insert(position,readyInformation);
}

