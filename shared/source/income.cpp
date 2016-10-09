#include "income.h"

using namespace rotable;

QString rotable::Income::_format = QString("dd MM yyyy");

//------------------------------------------------------------------------------

QJsonValue Income::toJSON() const
{
    QJsonObject o;
    o["id"] = _id;
    o["date"] = _date.toString(_format);
    o["format"] = _format;
    o["income"] = _income;

    return QJsonValue(o);
}

//------------------------------------------------------------------------------

rotable::Income *Income::fromJSON(const QJsonValue &jval)
{
    QJsonObject o = jval.toObject();
    // Check if all requaier fields are exists
    if (o.contains("id")
        && o.contains("date")
        && o.contains("format")
        && o.contains("income")
        )
    {
      // Create new Income base on JSON
      Income* i = new Income();
      i->_id = o["id"].toInt();
      i->_income = o["income"].toDouble();
      i->_format = o["format"].toString();
      i->setFormatedDate(o["date"].toString());

      return i;
    }

    return 0;
}

//------------------------------------------------------------------------------
