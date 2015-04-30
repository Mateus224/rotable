#include "include/orderpage.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

OrderPage::OrderPage(int clientID, QObject *parent)
    : QObject(parent)
{

}

OrderPage::~OrderPage()
{

}


void OrderPage::addToList(int clientID)
{
    OrderFromClient.append(new ProductOrder(_orderID,this));
}
