#ifndef ORDERINFORMATION_H
#define ORDERINFORMATION_H
#include <QObject>
#include <QTime>
#include <QDebug>

class OrderInformation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int pieces READ pieces WRITE setpieces NOTIFY piecesChanged)
    Q_PROPERTY(QString orderName READ orderName WRITE setorderName NOTIFY orderNameChanged)
    Q_PROPERTY(float price READ price WRITE setprice NOTIFY priceChanged)
    Q_PROPERTY(QString color_oderinfo READ info_orderInfo WRITE setinfo_orderInfo NOTIFY info_orderInfoChanged)


public:
    OrderInformation(QObject *parent=0);
    OrderInformation(const int &pieces,const QString &orderName,
                     const float &price, const QString &info_orderInfo,  QObject *parent=0);


    int pieces() const;
    void setpieces(const int &pieces);

    QString orderName() const;
    void setorderName(const QString &orderName);

    float price() const;
    void setprice(const float &price);

    QString info_orderInfo() const;
    void setinfo_orderInfo(const QString &info_orderInfo);
    float m_price;

    int resetStopWatch()const;
    void setresetStopWatch(const int &delet);

signals:

    void piecesChanged();
    void orderNameChanged();
    void priceChanged();
    void info_orderInfoChanged();

private:
    QString m_info_orderInfo;
    QString m_name;
    QString m_order;
    int m_pieces;
    QString m_orderName;
    QString m_ready;
    QString m_cancellation;
    QTime stopwatch;
};

#endif // ORDERINFORMATION_H
