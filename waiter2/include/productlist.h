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
#include <QMap>
#endif

#ifndef QSTRING_H
#include <QString>
#endif

#include "product.h"
#include "productcontainer.h"

//-----------------------------------------------------

class rotable::ProductList: public QObject
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

    //-----------------------------------------------------
    // Method for waiter_client
    //-----------------------------------------------------

    /**
     * Add product to list
     *
     * @param product       Product object
     */
    void addProduct(rotable::Product *product);

    /**
     * Remove product from list
     *
     * @param id            Product id
     * @return              true on success, false when product not exist
     */
    bool removeProduct(const int &id);

    /**
     * Update product name
     *
     * @param product       Product object
     * @return              true on success, false when product not exist
     */
    bool updateProduct(const rotable::Product *product);

    /**
     * Add pointer of ProductContainer to ProductList
     *
     * @param container     ProductContainer obj
     * @return              true if container exists
     */
    bool setContainer(rotable::ProductContainer *container);

    /**
     * Get name of product
     *
     * @param idx           Produt id
     * @return              Product name in QString
     */
    Q_INVOKABLE QString productName(const int &idx) const;

    /**
     * Return products count
     * @return  count
     */
    int count() const;

signals:
    void productNameChanged(int id);

public slots:

    //-----------------------------------------------------
    // Signals for ProductContainer
    //-----------------------------------------------------
    void productAdded(int id);
    void productRemoved(rotable::Product* product);
    void productUpdated(rotable::Product* product);

private:
    QMap<int, QString> _productList;
    rotable::ProductContainer *_container;
};

//-----------------------------------------------------

#endif //ROTABLE_PRODUCTLIST_H
