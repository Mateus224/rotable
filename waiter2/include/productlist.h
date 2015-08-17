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

#ifndef QHASH_H
#include <QHash>
#endif

#ifndef QSTRING_H
#include <QString>
#endif

#include "product.h"

//-----------------------------------------------------

class rotable::ProductList: QObject
{
    Q_OBJECT
public:

    //-----------------------------------------------------
    // Default destructor and construcor
    //-----------------------------------------------------

    /**
     * Default constructor
     *
     * @param parent        Parent object
     */
    ProductList(QObject *parent = 0);

signals:
    void productNameChanged();

public slots:
    /**
     * Get name of product
     *
     * @param idx           Produt id
     * @return              Product name in QString
     */
    QString productName(const int &idx) const;

private:
    QHash<int, QString> _productList;
};

//-----------------------------------------------------

#endif //ROTABLE_PRODUCTLIST_H
