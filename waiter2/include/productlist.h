#ifndef ROTABLE_PRODUCTLIST_H
#define ROTABLE_PRODUCTLIST_H

//-----------------------------------------------------

namespace rotable{
    class ProductList;
}

//-----------------------------------------------------

#ifndef QOBJECT_H
#include <QObject>
#endif

//-----------------------------------------------------

class rotable::ProductList: QObject
{
    Q_OBJECT
public:
    ProductList(QObject *parent = 0);
};

//-----------------------------------------------------

#endif //ROTABLE_PRODUCTLIST_H
