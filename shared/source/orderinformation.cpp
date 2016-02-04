#include <QDebug>
#include "../include/orderinformation.h"


OrderInformation::OrderInformation(QObject *parent) : QObject(parent)
{
}


OrderInformation::OrderInformation(const int &pieces,const QString &orderName,
                                   const float &price, const QString &info_orderInfo , QObject *parent)
    : QObject(parent), m_price(price*pieces), m_info_orderInfo(info_orderInfo), m_pieces(pieces), m_orderName(orderName)
{

    stopwatch.start();

}


//-----------------------------------------------------------------
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
        m_price= price;
        emit priceChanged();
    }
}


//-----------------------------------------------------------------
QString OrderInformation::info_orderInfo() const
{
    return m_info_orderInfo;
}

void OrderInformation::setinfo_orderInfo(const QString &info_orderInfo)
{
    if(info_orderInfo=="black"){
        m_info_orderInfo= "black";
        emit info_orderInfoChanged();
    }
    else if (info_orderInfo == "green") {
        m_info_orderInfo = "green";
        qDebug()<<(stopwatch.elapsed()/1000);
        emit info_orderInfoChanged();
    }
    else if(info_orderInfo=="red"){
        m_info_orderInfo= "red";
        emit info_orderInfoChanged();
    }
    else if(info_orderInfo=="white"){
        m_info_orderInfo= "white";
        emit info_orderInfoChanged();
    }
    else
    {
        m_info_orderInfo="blue";
        emit info_orderInfoChanged();
     }

}


