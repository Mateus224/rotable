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
  Q_PROPERTY(QString amount READ amount WRITE setAmount NOTIFY amountChanged)

public:
  explicit Product(const QJsonValue& jval, QObject *parent = 0);
  Product(QObject *parent = 0);

  inline const QString& name() const { return _name; }
  void setName(const QString &str);

  inline const QString& icon() const { return _icon; }
  void setIcon(const QString &ico);

  inline int price() const { return _price; }
  void setPrice(int price);
  inline const QString& priceStr() const { return _priceStr; }

  inline const QString& info() const { return _info; }
  void setInfo(const QString &info);

  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; }

  inline int categoryId() const { return _categoryId; }
  inline void setCategoryId(int categoryId) { _categoryId = categoryId; }

  inline const QString& amount() const { return _amount; }
  void setAmount(const QString& amount);



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
  void amountChanged();

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

  /* Product amount information */
  QString _amount;
}; // class Product

//------------------------------------------------------------------------------

#endif // ROTABLE_PRODUCT_H
