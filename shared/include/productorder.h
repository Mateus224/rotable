#ifndef ROTABLE_PRODUCTORDER_H
#define ROTABLE_PRODUCTORDER_H

//------------------------------------------------------------------------------

#include <QObject>

//------------------------------------------------------------------------------

namespace rotable {
  class ProductOrder;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::ProductOrder class contains a product order.
 */
class rotable::ProductOrder : public QObject
{
  Q_OBJECT

  /*
  Q_PROPERTY(int id READ id WRITE setId)
  Q_PROPERTY(int productId READ productId WRITE setProductId NOTIFY productIdChanged)
  Q_PROPERTY(int count READ count WRITE setSetCount NOTIFY countChanged)
  Q_PROPERTY(QString session READ session WRITE setSession NOTIFY sessionChanged)
  Q_PROPERTY(QString waitorId READ waitorId WRITE setWaitorId NOTIFY waitorChanged)
  Q_PROPERTY(int timestamp READ timestamp WRITE setTimeStamp NOTIFY timestampChanged)
  Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
  Q_PROPERTY(QString tableId READ tableId WRITE setTableId NOTIFY tableIdChanged)
  */

public:
  enum OrderState {
    /* The client is currently collecting this order */
    e_preparing = 0,

    /* The order has been submitted */
    e_submitted,

    /* The order has been accepted by a waitor */
    //e_accepted,

    /* The order has been delivered to the client */
    e_delivered,

    /* The order has been paid and is finished */
    e_finished,

    /* The order has been canceled */
    e_canceled
  };

  explicit ProductOrder(QObject *parent = 0);

  inline int id() const { return _id; }
  inline void setId(int id) { _id = id; }

  /**
   * Convert this order into a QJsonObject.
   *
   * @return            QJsonObject
   */
  QJsonValue toJSON() const;

  /**
   * Create an order object from a JSON value.
   *
   * @param jval        JSON value
   * @return            created order or NULL on error
   */
  static ProductOrder *fromJSON(const QJsonValue& jval);

signals:

private:

  /* Unique category ID */
  int _id;
}; // class ProductOrder

//------------------------------------------------------------------------------

#endif // ROTABLE_PRODUCTORDER_H
