#ifndef MYTABLES_H
#define MYTABLES_H
#include "private/precomp.h"
//#include "orderinformation.h"


//------------------------------------------------------------------------------

namespace rotable {
  class myTables;
  class Product;
}

//------------------------------------------------------------------------------

/**
 * @brief
 *
 */
class myTables : public QObject//, public OrderInformation
{
    Q_OBJECT
    Q_PROPERTY(QString color READ NewOrder WRITE setNewOrder NOTIFY NewOrderChanged)
    Q_PROPERTY(QString CallWaiter READ CallWaiter WRITE setCallWaiter NOTIFY CallWaiterChanged)
    Q_PROPERTY(QString currentIndexT READ tableNumber WRITE settableNumber NOTIFY tableNumberChanged)
    Q_PROPERTY(double ToPay READ toPay WRITE setToPay NOTIFY toPayChanged)




public:
    /**
     * @brief
     *
     * @param parent
     */
    myTables(QObject *parent=0);

    /**
     * @brief
     *
     * @return QString
     */
    QString tableNumber() const;
    /**
     * @brief
     *
     * @param tableNumber
     */
    void settableNumber(const QString &tableNumber);



    /**
     * @brief
     *
     * @param tables
     */
    void add_table(QString tables);
    /**
     * @brief
     *
     * @param m_pieces
     * @param m_orderName
     * @param m_price
     * @param m_info_orderInfo
     */
    void add_orderinformation(const int m_pieces,const QString m_orderName,const float m_price,const QString m_info_orderInfo);

    /**
     * @brief
     *
     * @return QString
     */
    QString CallWaiter() const;
    /**
     * @brief
     *
     * @param CallWaiter
     */
    void setCallWaiter(const QString &CallWaiter);

    /**
     * @brief
     *
     * @return QString
     */
    QString NewOrder() const;
    /**
     * @brief
     *
     * @param NewOrder
     */
    void setNewOrder(const QString &NewOrder);

    /**
     * @brief
     *
     * @return double
     */
    double toPay()const;
    /**
     * @brief
     *
     * @param toPay
     */
    void setToPay(const double &toPay);

    /**
     * @brief
     *
     * @param position
     * @param color
     */
    void setColor_orderinformation(const int &position,const QString &color);


    //QList <OrderInformation*>  L_orderinformation; /**< TODO: describe */





    QString m_tableNumber; /**< TODO: describe */
    float m_price; /**< TODO: describe */
    float m_toPay; /**< TODO: describe */

signals:
    /**
     * @brief
     *
     */
    void NewOrderChanged();
    /**
     * @brief
     *
     */
    void CallWaiterChanged();
    /**
     * @brief
     *
     */
    void tableNumberChanged();
    /**
     * @brief
     *
     */
    void toPayChanged();

public slots:



private:
    int m__quantity; /**< TODO: describe */
    QString m_newOrder; /**< TODO: describe */
    QString m_CallWaiter; /**< TODO: describe */
    QString m_name; /**< TODO: describe */
    QString m_order; /**< TODO: describe */
    int m_pieces; /**< TODO: describe */
    QString m_orderName; /**< TODO: describe */
    QString m_ready; /**< TODO: describe */
    QString m_cancellation; /**< TODO: describe */

};

#endif // MYTABLES_H
