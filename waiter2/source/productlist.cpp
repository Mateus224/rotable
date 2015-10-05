#include "productlist.h"

//-----------------------------------------------------

using namespace rotable;

//-----------------------------------------------------

rotable::ProductList::ProductList(QObject *parent): QObject(parent)
{

}

//-----------------------------------------------------

void ProductList::addProduct(Product *product)
{

    _productList[product->id()] = product->name();
}

//-----------------------------------------------------

bool ProductList::removeProduct(const int &id)
{
    if(_productList.contains(id))
    {
        _productList.remove(id);
        return true;
    }
    else
        return false;
}

//-----------------------------------------------------

bool ProductList::updateProduct(const Product *product)
{
    if(_productList.contains(product->id()))
    {
        _productList[product->id()] = product->name();
        emit productNameChanged(product->id());
        return true;
    }
    else
        return false;
}

//-----------------------------------------------------

bool ProductList::setContainer(ProductContainer *container)
{
    //Check if container exists
    if(!container)
        return false;

    //Assign pointer
    _container = container;
    //Connect slost
    connect(container, &ProductContainer::productAdded, this, &ProductList::productAdded);
    connect(container, &ProductContainer::productUpdated, this, &ProductList::productUpdated);
    connect(container, &ProductContainer::productRemoved, this, &ProductList::productRemoved);
    //Return true
    return true;
}

//-----------------------------------------------------

QString ProductList::productName(const int &idx) const
{
    if(_productList.contains(idx))
        return _productList[idx];
    else
    {
        qCritical() << "Product doesn't exist";
        return "";
    }
}

int ProductList::count() const
{
    return _productList.count();
}

//-----------------------------------------------------

void ProductList::productAdded(int id)
{
    qDebug() << "Product add id" << id;
    addProduct(_container->product(id));
}

//-----------------------------------------------------

void ProductList::productRemoved(Product *product)
{
    removeProduct(product->id());
}

//-----------------------------------------------------

void ProductList::productUpdated(Product *product)
{
    updateProduct(product);
}

//-----------------------------------------------------
