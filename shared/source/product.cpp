#include "private/precomp.h"

#include "product.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

Product::Product(QObject *parent) :
  QObject(parent), _id(-1)
{

}

//------------------------------------------------------------------------------

void Product::setPrice(int price)
{
  _price = price;

  // add ',' to price string
  QString pStr = QString("%1").arg(price);
  if (price < 100) {
    pStr = "0," + pStr;
  } else {
    pStr = pStr.mid(0, pStr.length() - 2) + "," + pStr.right(2);
  }

  _priceStr = pStr + " €";

  emit priceChanged();
}

//------------------------------------------------------------------------------

QJsonValue Product::toJSON() const
{
  QJsonObject o;
  o["id"] = _id;
  o["categoryId"] = _categoryId;
  o["name"] = _name;
  o["icon"] = _icon;
  o["price"] = _price;
  o["priceStr"] = _priceStr;
  o["info"] = _info;
  return QJsonValue(o);
}

//------------------------------------------------------------------------------

Product *Product::fromJSON(const QJsonValue &jval)
{
  QJsonObject o = jval.toObject();

  if (o.contains("name")
      && o.contains("info")
      && o.contains("icon")
      && o.contains("id")
      && o.contains("price")
      && o.contains("categoryId"))
  {
    Product* p = new Product();
    p->_name = o["name"].toString();
    p->_info = o["info"].toString();
    p->_icon = o["icon"].toString();
    p->_id = o["id"].toInt();
    p->_price = o["price"].toInt();
    p->setPrice(p->_price);
    p->_categoryId = o["categoryId"].toInt();

    return p;
  }

  return 0;
}
