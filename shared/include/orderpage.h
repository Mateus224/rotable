#ifndef ORDERPAGE_H
#define ORDERPAGE_H

#ifndef QOBJECT_H
#include <QObject>
#endif
#include <QList>
#include "orderpage.h"
#include "productorder.h"

//------------------------------------------------------------------------------

namespace rotable {
  class ProductOrder;
  class OrderPage;
}

//------------------------------------------------------------------------------
/**
  Here we will communicate with the Gui
  */





//------------------------------------------------------------------------------

class rotable::OrderPage :public QObject
{
    Q_OBJECT
public:
    OrderPage(int clientID, QObject *parent = 0);
    ~OrderPage();

    void addToList(int clientID);

    /**
     * @brief OrderFromClient
     * stores the Orders from a Client befor he send them
     */
    QList<ProductOrder*> OrderFromClient;

private:
    int _orderID;
};

#endif // ORDERPAGE_H
