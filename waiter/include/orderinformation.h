#ifndef ORDERINFORMATION_H
#define ORDERINFORMATION_H
//#include<../include/table.h>
#include <QObject>

class OrderInformation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ order WRITE setorder NOTIFY orderChanged)
    Q_PROPERTY(int pieces READ pieces WRITE setpieces NOTIFY piecesChanged)
    Q_PROPERTY(QString orderName READ orderName WRITE setorderName NOTIFY orderNameChanged)
    Q_PROPERTY(float price READ price WRITE setprice NOTIFY priceChanged)
    Q_PROPERTY(bool ready READ ready WRITE setready NOTIFY readyChanged)
    Q_PROPERTY(bool cancellation READ cancellation WRITE setcancellation NOTIFY cancellationChanged)


public:
    OrderInformation(QObject *parent=0);
    OrderInformation(const QString &name, const QString &order, const int &pieces,const QString &orderName,
                     const float &price, const bool &ready, const bool &cancellation,  QObject *parent=0);

    QString name() const;
    void setName(const QString &name);

    QString order() const;
    void setorder(const QString &order);

    int pieces() const;
    void setpieces(const int &pieces);

    QString orderName() const;
    void setorderName(const QString &orderName);

    float price() const;
    void setprice(const float &price);

    bool ready() const;
    void setready(const bool &ready);

    bool cancellation() const;
    void setcancellation(const bool &cancellation);

    //float time() const;
    //void settime(const float &time);

public slots:
    //void currentTableObject(int index);
    void cppSlot(const QString &msg) {
            qDebug() << "Called the C++ slot with message:" << msg;
        }

signals:
    void nameChanged();
    void orderChanged();
    void piecesChanged();
    void orderNameChanged();
    void priceChanged();
    void readyChanged();
    void cancellationChanged();
    //void timeChanged();

private:
    QString m_name;
    QString m_order;
    int m_pieces;
    QString m_orderName;
    float m_price;
    bool m_ready;
    bool m_cancellation;
    //QString m_time;
};

#endif // ORDERINFORMATION_H
