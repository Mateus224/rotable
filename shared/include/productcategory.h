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
  Q_PROPERTY(int sequence READ sequence WRITE setSequence NOTIFY sequenceChanged)

public:
  /**
   * @brief
   *
   * @param parent
   */
  explicit ProductCategory(QObject *parent = 0);

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
  void sequenceChanged();

private:
  /* Category name */
  QString _name;

  /* Category icon */
  QString _icon;

  /* Unique category ID */
  int _id;

  int _sequence;
}; // class ProductCategory

//------------------------------------------------------------------------------

#endif // ROTABLE_PRODUCTCATEGORY_H
