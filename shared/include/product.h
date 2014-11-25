#ifndef ROTABLE_PRODUCT_H
#define ROTABLE_PRODUCT_H

//------------------------------------------------------------------------------

#ifndef QICON_H
#include <QIcon>
#endif

#ifndef QJSONOBJECT_H
#include <QJsonObject>
#endif

//------------------------------------------------------------------------------

namespace rotable {
  class Product;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::Product class defines a product.
 */
class rotable::Product : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
  Q_PROPERTY(int price READ price WRITE setPrice NOTIFY priceChanged)
  Q_PROPERTY(QString priceStr READ priceStr NOTIFY priceChanged)
  Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged)
  Q_PROPERTY(int id READ id WRITE setId)

public:
  explicit Product(const QJsonValue& jval, QObject *parent = 0);
  explicit Product(QObject *parent = 0);

  inline const QString& name() const { return _name; }
  inline void setName(const QString &str) { _name = str; emit nameChanged(); }

  inline const QString& icon() const { return _icon; }
  inline void setIcon(const QString &ico) { _icon = ico; emit iconChanged(); }

  inline int price() const { return _price; }
  void setPrice(int price);
  inline const QString& priceStr() const { return _priceStr; }

  inline const QString& info() const { return _info; }
  inline void setInfo(const QString &info) { _info = info; emit infoChanged(); }

  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; }

  inline int categoryId() const { return _categoryId; }
  inline void setCategoryId(int categoryId) { _categoryId = categoryId; }

  /**
   * Convert this product category into a QJsonObject.
   *
   * @return            QJsonValue
   */
  QJsonValue toJSON() const;

  /**
   * Create a product object from a JSON value.
   *
   * @param jval        JSON value
   * @return            created product or NULL on error
   */
  static Product *fromJSON(const QJsonValue& jval);

signals:
  void nameChanged();
  void iconChanged();
  void priceChanged();
  void infoChanged();

private:
  /* Unique product ID */
  int _id;

  /* Unique category ID */
  int _categoryId;

  /* Product name */
  QString _name;

  /* Product icon */
  QString _icon;

  /* Product price in cents */
  int _price;

  /* Product price as string */
  QString _priceStr;

  /* Product info string */
  QString _info;
}; // class Product

//------------------------------------------------------------------------------

#endif // ROTABLE_PRODUCT_H
