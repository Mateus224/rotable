#ifndef ORDERINFORMATION_H
#define ORDERINFORMATION_H
#include <QObject>
#include <QTime>
#include <QDebug>

/**
 * @brief
 *
 */
class OrderInformation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int pieces READ pieces WRITE setpieces NOTIFY piecesChanged)
    Q_PROPERTY(QString orderName READ orderName WRITE setorderName NOTIFY orderNameChanged)
    Q_PROPERTY(float price READ price WRITE setprice NOTIFY priceChanged)
    Q_PROPERTY(QString color_oderinfo READ info_orderInfo WRITE setinfo_orderInfo NOTIFY info_orderInfoChanged)


public:
    /**
     * @brief
     *
     * @param parent
     */
    OrderInformation(QObject *parent=0);
    /**
     * @brief
     *
     * @param pieces
     * @param orderName
     * @param price
     * @param info_orderInfo
     * @param parent
     */
    OrderInformation(const int &pieces,const QString &orderName,
                     const float &price, const QString &info_orderInfo,  QObject *parent=0);


    /**
     * @brief
     *
     * @return int
     */
    int pieces() const;
    /**
     * @brief
     *
     * @param pieces
     */
    void setpieces(const int &pieces);

    /**
     * @brief
     *
     * @return QString
     */
    QString orderName() const;
    /**
     * @brief
     *
     * @param orderName
     */
    void setorderName(const QString &orderName);

    /**
     * @brief
     *
     * @return float
     */
    float price() const;
    /**
     * @brief
     *
     * @param price
     */
    void setprice(const float &price);

    /**
     * @brief
     *
     * @return QString
     */
    QString info_orderInfo() const;
    /**
     * @brief
     *
     * @param info_orderInfo
     */
    void setinfo_orderInfo(const QString &info_orderInfo);
    float m_price; /**< TODO: describe */

    /**
     * @brief
     *
     * @return int
     */
    int resetStopWatch()const;
    /**
     * @brief
     *
     * @param delet
     */
    void setresetStopWatch(const int &delet);

signals:

    /**
     * @brief
     *
     */
    void piecesChanged();
    /**
     * @brief
     *
     */
    void orderNameChanged();
    /**
     * @brief
     *
     */
    void priceChanged();
    /**
     * @brief
     *
     */
    void info_orderInfoChanged();

private:
    QString m_info_orderInfo; /**< TODO: describe */
    QString m_name; /**< TODO: describe */
    QString m_order; /**< TODO: describe */
    int m_pieces; /**< TODO: describe */
    QString m_orderName; /**< TODO: describe */
    QString m_ready; /**< TODO: describe */
    QString m_cancellation; /**< TODO: describe */
    QTime stopwatch; /**< TODO: describe */
};

#endif // ORDERINFORMATION_H
