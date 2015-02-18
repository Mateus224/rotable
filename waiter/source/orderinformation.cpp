#include <QDebug>
#include "../include/orderinformation.h"


OrderInformation::OrderInformation(QObject *parent) : QObject(parent)
{
}


OrderInformation::OrderInformation(const QString &name, const QString &order, const int &pieces,const QString &orderName,
                                   const float &price, const bool &ready, const bool &cancellation , QObject *parent)
    : QObject(parent), m_name(name), m_order(order), m_pieces(pieces), m_orderName(orderName), m_price(price), m_ready(ready),m_cancellation(cancellation)
{
}


//-----------------------------------------------------------------
QString OrderInformation::name() const
{
    return m_name;
}

void OrderInformation::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged();
    }
}


//-----------------------------------------------------------------
QString OrderInformation::order() const
{
    return m_order;
}

void OrderInformation::setorder(const QString &order)
{
    if (order != m_order) {
        m_order = order;
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
        m_price = price;
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
/*QString OrderInformation::order() const
{
    return m_order;
}

void OrderInformation::setorder(const QString &order)
{
    if (order != m_order) {
        m_order = order;
        emit orderChanged();
    }
}*/
