#ifndef ROTABLE_PRODUCTCATEGORY_H
#define ROTABLE_PRODUCTCATEGORY_H

//------------------------------------------------------------------------------

#ifndef QICON_H
#include <QIcon>
#endif

#ifndef QJSONOBJECT_H
#include <QJsonObject>
#endif

#include "product.h"

//------------------------------------------------------------------------------

namespace rotable {
  class ProductCategory;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::ProductCategory class contains a product name and a
 * set of products.
 */
class rotable::ProductCategory : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
  Q_PROPERTY(int id READ id WRITE setId)

public:
  explicit ProductCategory(QObject *parent = 0);

  inline const QString& name() const { return _name; }
  void setName(const QString &str);

  inline const QString& icon() const { return _icon; }
  void setIcon(const QString &ico);

  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; }

  /**
   * Convert this product category into a QJsonObject.
   *
   * @return            QJsonObject
   */
  QJsonValue toJSON() const;

  /**
   * Create a product category object from a JSON value.
   *
   * @param jval        JSON value
   * @return            created product category or NULL on error
   */
  static ProductCategory *fromJSON(const QJsonValue& jval);

signals:
  void nameChanged();
  void iconChanged();

private:
  /* Category name */
  QString _name;

  /* Category icon */
  QString _icon;

  /* Unique category ID */
  int _id;
}; // class ProductCategory

//------------------------------------------------------------------------------

#endif // ROTABLE_PRODUCTCATEGORY_H
