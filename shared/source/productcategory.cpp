#include "private/precomp.h"

#include "productcategory.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ProductCategory::ProductCategory(QObject* parent) :
  QObject(parent), _id(-1)
{

}

//------------------------------------------------------------------------------

QJsonValue ProductCategory::toJSON() const
{
  QJsonObject o;
  o["name"] = _name;
  o["icon"] = _icon;
  o["id"] = _id;
  return QJsonValue(o);
}

//------------------------------------------------------------------------------

ProductCategory *ProductCategory::fromJSON(const QJsonValue &jval)
{
  QJsonObject o = jval.toObject();

  if (o.contains("name")
      && o.contains("icon")
      && o.contains("id"))
  {
    ProductCategory* c = new ProductCategory();
    c->_name = o["name"].toString();
    c->_icon = o["icon"].toString();
    c->_id = o["id"].toInt();

    return c;
  }

  return 0;
}
