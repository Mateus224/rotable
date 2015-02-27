#include <QDebug>
#include "../include/orderinformation.h"


OrderInformation::OrderInformation(QObject *parent) : QObject(parent)
{
}


OrderInformation::OrderInformation(const QString &neworder, const int &pieces,const QString &orderName,
                                   const float &price, const bool &ready, const bool &cancellation , QObject *parent)
    : QObject(parent), m_order(neworder), m_pieces(pieces), m_orderName(orderName), m_price(price), m_ready(ready),m_cancellation(cancellation)
{
}



//-----------------------------------------------------------------
QString OrderInformation::order() const
{
    return m_order;
}

void OrderInformation::setorder(const QString &neworder)
{
    if (neworder != m_order) {
        m_order = neworder;
        emit orderChanged();
    }
}


//-----------------------------------------------------------------
int OrderInformation::pieces() const
{
    return m_pieces;
}

void OrderInformation::setpieces(const int &pieces)
{
    if (pieces != m_pieces) {
        m_pieces = pieces;
        emit piecesChanged();
    }
}


//-----------------------------------------------------------------
QString OrderInformation::orderName() const
{
    return m_orderName;
}

void OrderInformation::setorderName(const QString &orderName)
{
    if (orderName != m_orderName) {
        m_orderName = orderName;
        emit orderNameChanged();
    }
}


//-----------------------------------------------------------------
float OrderInformation::price() const
{
    return m_price;
}

void OrderInformation::setprice(const float &price)
{
    if (price != m_price) {
        //m_price = (float)((int)(price*100))/100;
        m_price= price;
        emit priceChanged();
    }
}


//-----------------------------------------------------------------
bool OrderInformation::ready() const
{
    return m_ready;
}

void OrderInformation::setready(const bool &ready)
{
    if (ready != m_ready) {
        m_ready = ready;
        emit readyChanged();
    }
}


//-----------------------------------------------------------------
bool OrderInformation::cancellation() const
{
    return m_cancellation;
}

void OrderInformation::setcancellation(const bool &cancellation)
{
    if (cancellation != m_cancellation) {
        m_cancellation = cancellation;
        emit cancellationChanged();
    }
}


//-----------------------------------------------------------------
