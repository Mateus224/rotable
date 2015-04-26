#include "neworder.h"
#include "private/precomp.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

/*
NewOrder::NewOrder(QObject *parent)
    : QObject(parent)
{
    //_orderId=0;
}*/




void NewOrder::New_Order(int clientID)
{
    _clientID=clientID;
    Order=new rotable::ProductOrder(_orderID, _clientID,this);
    _orderID++;
}


