#include "neworder.h"
#include "private/precomp.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------


NewOrder::NewOrder(QObject *parent)
    : QObject(parent)
{
    _orderID=0;
}




void NewOrder::TableClient(int clientID)
{
    _clientID=clientID;
    Order.append( new OrderPage(_clientID,this));
}



/**
  NewOrder have a List of OrderPages in this Pages are an OrderID and a ClientID
  New Order append a page or remove this from the Page
  Every page have a QList of productorder
  A ProductOrder have the quantity the the product which is
  identifyered by the ProductID
  */

