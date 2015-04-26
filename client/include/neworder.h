#ifndef NEWORDER_H
#define NEWORDER_H

#ifndef QOBJECT_H
#include <QObject>
#endif
#include "productorder.h"

namespace rotable {
  class ProductOrder;
  class NewOrder;
}

class rotable::NewOrder : public QObject
{

   Q_OBJECT


public:
    explicit NewOrder(QObject *parent = 0){_orderID=0;}
    ~NewOrder();


private:
    rotable::ProductOrder* Order;
    int _orderID;
    int _clientID;



public slots:
    //void Payed();
    void New_Order(int clientID);
};

#endif // NEWORDER_H
