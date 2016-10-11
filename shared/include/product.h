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
  Q_PROPERTY(int sequence READ sequence WRITE setSequence NOTIFY sequenceChanged)

public:
  /**
   * @brief
   *
   * @param jval
   * @param parent
   */
  explicit Product(const QJsonValue& jval, QObject *parent = 0);
  /**
   * @brief
   *
   * @param parent
   */
  Product(QObject *parent = 0);

  /**
   * @brief
   *
   * @return const QString
   */
  inline const QString& name() const { return _name; }
  /**
   * @brief
   *
   * @param str
   */
  void setName(const QString &str);

  /**
   * @brief
   *
   * @return const QString
   */
  inline const QString& icon() const { return _icon; }
  /**
   * @brief
   *
   * @param ico
   */
  void setIcon(const QString &ico);

  /**
   * @brief
   *
   * @return int
   */
  inline int price() const { return _price; }
  /**
   * @brief
   *
   * @param price
   */
  void setPrice(int price);
  /**
   * @brief
   *
   * @return const QString
   */
  inline const QString& priceStr() const { return _priceStr; }

  /**
   * @brief
   *
   * @return const QString
   */
  inline const QString& info() const { return _info; }
  /**
   * @brief
   *
   * @param info
   */
  void setInfo(const QString &info);

  /**
   * @brief
   *
   * @return int
   */
  inline int id() const { return _id; }
  /**
   * @brief
   *
   * @param id
   */
  inline void setId(int id) { _id = id; }

  /**
   * @brief
   *
   * @return int
   */
  inline int categoryId() const { return _categoryId; }
  /**
   * @brief
   *
   * @param categoryId
   */
  inline void setCategoryId(int categoryId) { _categoryId = categoryId; }

  /**
   * @brief
   *
   * @return const QString
   */
  inline const QString& amount() const { return _amount; }
  /**
   * @brief
   *
   * @param amount
   */
  void setAmount(const QString& amount);

  /**
   * @brief
   *
   * @return int
   */
  inline  int sequence() const { return _sequence; }
  /**
   * @brief
   *
   * @param sequence
   */
  inline void setSequence(int sequence) { _sequence = sequence; emit sequenceChanged();}
  /**
   * @brief
   *
   */
  inline void up() { --_sequence; emit sequenceChanged(); }
  /**
   * @brief
   *
   */
  inline void down() { ++_sequence; emit sequenceChanged(); }

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
  /**
   * @brief
   *
   */
  void nameChanged();
  /**
   * @brief
   *
   */
  void iconChanged();
  /**
   * @brief
   *
   */
  void priceChanged();
  /**
   * @brief
   *
   */
  void infoChanged();
  /**
   * @brief
   *
   */
  void amountChanged();
  /**
   * @brief
   *
   */
  void sequenceChanged();

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

  /* Sequence in category*/
  int _sequence;
}; // class Product

//------------------------------------------------------------------------------

#endif // ROTABLE_PRODUCT_H
