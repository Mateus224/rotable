#include "private/precomp.h"

#include "productcategory.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ProductCategory::ProductCategory(QObject* parent) :
  QObject(parent), _id(-1), _sequence(-1)
{

}

//------------------------------------------------------------------------------

void ProductCategory::setName(const QString &str)
{
  if (_name != str) {
    _name = str;
    emit nameChanged();
  }
}

//------------------------------------------------------------------------------

void ProductCategory::setIcon(const QString &ico)
{
  if (_icon != ico) {
    _icon = ico;
    emit iconChanged();
  }
}

//------------------------------------------------------------------------------

QJsonValue ProductCategory::toJSON() const
{
  QJsonObject o;
  o["name"] = _name;
  o["icon"] = _icon;
  o["id"] = _id;
  o["sequence"] = _sequence;
  return QJsonValue(o);
}

//------------------------------------------------------------------------------

ProductCategory *ProductCategory::fromJSON(const QJsonValue &jval)
{
  QJsonObject o = jval.toObject();

  if (o.contains("name")
      && o.contains("icon")
      && o.contains("id")
      && o.contains("sequence"))
  {
    ProductCategory* c = new ProductCategory();
    c->_name = o["name"].toString();
    c->_icon = o["icon"].toString();
    c->_id = o["id"].toInt();
    c->_sequence = o["sequence"].toInt();

    return c;
  }

  return 0;
}
