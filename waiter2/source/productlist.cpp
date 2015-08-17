#include "productlist.h"

//-----------------------------------------------------

using namespace rotable;

//-----------------------------------------------------

rotable::ProductList::ProductList(QObject *parent): QObject(parent)
{

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
