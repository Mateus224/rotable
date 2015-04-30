#include "private/precomp.h"

#include "productorder.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ProductOrder::ProductOrder(int orderID, QObject *parent) : QObject(parent)
{
    _orderID=orderID;
    //L_quantity= new QList<int>;
    //L_OrderList= new QList<int>;
}

ProductOrder::ProductOrder::~ProductOrder()
{

}


//------------------------------------------------------------------------------

void ProductOrder::addProductToOrder(int id)
{
    //L_quantity->append(_productId);
    //L_OrderList->append(_quantity);
}

void ProductOrder::removeProductFromOrder(int id)
{

}

void ProductOrder::sendOrderToServer()
{

}

void ProductOrder::sendOrderToWaitor()
{

}

void ProductOrder::acceptOrder()
{

}

void ProductOrder::setStopWatchTime()
{

}

int ProductOrder::getStopWatchTime()
{

    return 0;
}

int ProductOrder::sendWaitTimeForClient()
{

    return 0;
}
//------------------------------------------------------------------------------



void ProductOrder::set_quantity(int id)
{
    _productId=id;
    addProductToOrder(id);
}
//------------------------------------------------------------------------------

static ProductOrder *fromJSON(const QJsonValue& jval)
{

}

QJsonValue ProductOrder::toJSON() const
{

}
