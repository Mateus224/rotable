#ifndef ORDERINFORMATION_H
#define ORDERINFORMATION_H
#include <QObject>
#include <QDebug>

class OrderInformation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString newOrder READ order WRITE setorder NOTIFY orderChanged)
    Q_PROPERTY(int pieces READ pieces WRITE setpieces NOTIFY piecesChanged)
    Q_PROPERTY(QString orderName READ orderName WRITE setorderName NOTIFY orderNameChanged)
    Q_PROPERTY(float price READ price WRITE setprice NOTIFY priceChanged)
    Q_PROPERTY(QString ready READ ready WRITE setready NOTIFY readyChanged)
    Q_PROPERTY(QString cancellation READ cancellation WRITE setcancellation NOTIFY cancellationChanged)


public:
    OrderInformation(QObject *parent=0);
    OrderInformation(const QString &neworder, const int &pieces,const QString &orderName,
                     const float &price, const QString &ready, const QString &cancellation,  QObject *parent=0);


    QString order() const;
    void setorder(const QString &neworder);

    int pieces() const;
    void setpieces(const int &pieces);

    QString orderName() const;
    void setorderName(const QString &orderName);

    float price() const;
    void setprice(const float &price);

    QString ready() const;
    void setready(const QString &ready);

    QString cancellation() const;
    void setcancellation(const QString &cancellation);
    float m_price;

signals:
 //   void nameChanged();
    void orderChanged();
    void piecesChanged();
    void orderNameChanged();
    void priceChanged();
    void readyChanged();
    void cancellationChanged();

private:
    QString m_name;
    QString m_order;
    int m_pieces;
    QString m_orderName;
    QString m_ready;
    QString m_cancellation;
};

#endif // ORDERINFORMATION_H
