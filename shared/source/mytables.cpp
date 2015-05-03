#include "../include/mytables.h"
#include <QDebug>
#include <QObject>

myTables::myTables(QObject *parent) : QObject(parent)
{
    ClientProductHash=new QHash<int,productChoosen>;
    ClientProductHash->reserve(250);
    m__quantity=0;
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

//------------------------------------------------------------
int myTables::quantity() const
{
    return Product._s_quantity;
}

void myTables::setquantity( int quantity)
{
    Product._s_quantity = quantity;
    emit quantityChanged();
}


//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Get Information
//-----------------------------------------------------------------


//-----------------------------------------------------------------


void myTables::addToProductHash(int ProductID)
{
    if(ClientProductHash->contains(ProductID))
    {
        Product=ClientProductHash->take(ProductID);
        Product._s_quantity++;
        ClientProductHash->insert(Product._s_id, Product);
/*
        QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
        while (i != ClientProductHash->constEnd()) {
            qDebug() <<  "quantity: " << i.value()._s_quantity <<  "id: " << i.value()._s_id ;
            ++i;
        }*/
        setquantity(Product._s_quantity);

    }
    else
    {
        productChoosen* Product=new productChoosen;
        Product->_s_id=ProductID;
        Product->_s_quantity=1;
        ClientProductHash->insert(Product->_s_id,*Product);
/*
        QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
        while (i != ClientProductHash->constEnd()) {
            qDebug() <<  "first; quantity: " << i.value()._s_quantity <<  "id: " << i.value()._s_id ;
            ++i;
        }*/
        setquantity(1);
    }

}

//-----------------------------------------------------------------


void myTables::rmFromProductHash(int ProductID)
{
    if(ClientProductHash->contains(ProductID))
    {
        Product=ClientProductHash->take(ProductID);
        if(Product._s_quantity>0)
        {
            Product._s_quantity--;
            ClientProductHash->insert(Product._s_id,Product);
/*
            QHash<int,productChoosen> ::const_iterator i = ClientProductHash->constBegin();
            while (i != ClientProductHash->constEnd()) {
            qDebug() <<  "rm; quantity: " << i.value()._s_quantity <<  "id: " << i.value()._s_id ;
                ++i;
            }*/
        }
        else if(Product._s_quantity==1);
        else
        {
            qDebug()<<"Fehler in rmFromProductHash1";
        }


    }
    else
    {
        qDebug()<<"Fehler in rmFromProductHash2";
    }
    setquantity(Product._s_quantity);
}

//-----------------------------------------------------------------

void myTables::getQuantity(int ProductID)
{
    if(ClientProductHash->contains(ProductID))
    {
        Product=ClientProductHash->take(ProductID);
        ClientProductHash->insert(Product._s_id,Product);
        setquantity (Product._s_quantity);
    }
    else
    {
        int zero=0;
        setquantity (zero);
    }
}

