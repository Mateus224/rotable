#ifndef NEWORDER_H
#define NEWORDER_H

#ifndef QOBJECT_H
#include <QObject>
#endif
#include "productorder.h"
#include "private/precomp.h"

namespace rotable {
  class ProductOrder;
  class NewOrder;
}

class rotable::NewOrder : public QObject
{

   Q_OBJECT


public:
     NewOrder(QObject *parent = 0);//{_orderID=0;}
    ~NewOrder(){};

     QList<rotable::OrderPage*> Order;

     void TableClient(int clientID);

private:
    //rotable::ProductOrder* Order;
    int _orderID;
    int _clientID;



public slots:
    //void Payed();

    /**
     * @brief New_Order
     * @param clientID
     *Here we manage the Order pages from all Clients
     */

};

#endif // NEWORDER_H
