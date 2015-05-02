#ifndef MYTABLES_H
#define MYTABLES_H
#include "private/precomp.h"
#include "orderinformation.h"

class myTables : public QObject//, public OrderInformation
{
    Q_OBJECT
    Q_PROPERTY(QString color READ NewOrder WRITE setNewOrder NOTIFY NewOrderChanged)
    Q_PROPERTY(QString CallWaiter READ CallWaiter WRITE setCallWaiter NOTIFY CallWaiterChanged)
    Q_PROPERTY(QString currentIndexT READ tableNumber WRITE settableNumber NOTIFY tableNumberChanged)
    Q_PROPERTY(double ToPay READ toPay WRITE setToPay NOTIFY toPayChanged)

    //Q_PROPERTY(int _s_quantity READ tableNumber WRITE settableNumber NOTIFY tableNumberChanged)



public:
    myTables(QObject *parent=0);

    QString tableNumber() const;
    void settableNumber(const QString &tableNumber);

    void add_table(QString tables);
    void add_orderinformation(const int m_pieces,const QString m_orderName,const float m_price,const QString m_info_orderInfo);

    QString CallWaiter() const;
    void setCallWaiter(const QString &CallWaiter);

    QString NewOrder() const;
    void setNewOrder(const QString &NewOrder);

    double toPay()const;
    void setToPay(const double &toPay);

    void setColor_orderinformation(const int &position,const QString &color);


    QList <OrderInformation*>  L_orderinformation;




    struct productChoosen{
        int _s_id;
        int _s_quantity;
    };
    productChoosen Product;

    QHash<int,productChoosen> ClientProductHash;

    QString m_tableNumber;
    float m_price;
    float m_toPay;

signals:
    void NewOrderChanged();
    void CallWaiterChanged();
    void tableNumberChanged();
    void toPayChanged();

public slots:

    void addToProductHash(int ProductID);
    void rmFromProductHash(int ProductID);

private:
    QString m_newOrder;
    QString m_CallWaiter;
    QString m_name;
    QString m_order;
    int m_pieces;
    QString m_orderName;
    QString m_ready;
    QString m_cancellation;

};

#endif // MYTABLES_H
