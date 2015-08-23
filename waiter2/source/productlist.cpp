#include "productlist.h"

//-----------------------------------------------------

using namespace rotable;

//-----------------------------------------------------

rotable::ProductList::ProductList(QObject *parent): QObject(parent)
{

}

//-----------------------------------------------------

void ProductList::addProduct(const Product *product)
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
       _container = container;
       connect(container, SIGNAL(productAdded(int)), this, SLOT(productAdded(int)));
       connect(container, SIGNAL(productUpdated(rotable::Product*)), this, SLOT(productUpdated(rotable::Product*)));
       connect(container, SIGNAL(productRemoved(rotable::Product*)), this, SLOT(productRemoved(rotable::Product*)));
}

//-----------------------------------------------------

QString ProductList::productName(const int &idx) const
{
    if(_productList.contains(idx))
        return _productList[idx];
    else
    {
        qCritical() << "Product don't exist";
        return QString("");
    }
}

//-----------------------------------------------------

void ProductList::productAdded(int id)
{

}

//-----------------------------------------------------

void ProductList::productRemoved(Product *product)
{

}

//-----------------------------------------------------

void ProductList::productUpdated(Product *product)
{

}

//-----------------------------------------------------
