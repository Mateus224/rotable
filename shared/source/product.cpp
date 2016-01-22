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

void Product::setName(const QString &str)
{
  if (_name != str) {
    _name = str;
    emit nameChanged();
  }
}

//------------------------------------------------------------------------------

void Product::setIcon(const QString &ico)
{
  if (_icon != ico) {
    _icon = ico;
    emit iconChanged();
  }
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

void Product::setInfo(const QString &info)
{
  if (_info != info) {
    _info = info;
    emit infoChanged();
  }
}

//------------------------------------------------------------------------------

void Product::setAmount(const QString &amount)
{
    qDebug()<<"Product::setAmount "<<amount;
  if (_amount != amount) {
    _amount = amount;
    emit amountChanged();
  }
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
  o["amount"] = _amount;
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
      && o.contains("categoryId")
      && o.contains("amount"))
  {
    Product* p = new Product();
    p->_name = o["name"].toString();
    p->_info = o["info"].toString();
    p->_icon = o["icon"].toString();
    p->_id = o["id"].toInt();
    p->_price = o["price"].toInt();
    p->setPrice(p->_price);
    p->_categoryId = o["categoryId"].toInt();
    p->_amount = o["amount"].toString();

    return p;
  }

  return 0;
}
