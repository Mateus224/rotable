#ifndef MYTABLES_H
#define MYTABLES_H
#include <QObject>
#include "orderinformation.h"

class myTables : public QObject//, public OrderInformation
{
    Q_OBJECT
    Q_PROPERTY(QString color READ NewOrder WRITE setNewOrder NOTIFY NewOrderChanged)
    Q_PROPERTY(QString CallWaiter READ CallWaiter WRITE setCallWaiter NOTIFY CallWaiterChanged)
    Q_PROPERTY(int currentIndexT READ tableNumber WRITE settableNumber NOTIFY tableNumberChanged)


public:
    myTables(QObject *parent=0);

    int tableNumber() const;
    void settableNumber(const int &tableNumber);
    void add_table(int tables);
    void add_orderinformation(const QString m_order, const int m_pieces,const QString m_orderName,const float m_price,const bool m_ready,const bool m_cancellation);
    void cancellation_orderinformation(int position);

    QString CallWaiter() const;
    void setCallWaiter(const QString &CallWaiter);

    QString NewOrder() const;
    void setNewOrder(const QString &NewOrder);


    void ready_orderinformation(int position);
    QList <OrderInformation*>  L_orderinformation;
    int m_tableNumber;

signals:
    void NewOrderChanged();
    void CallWaiterChanged();
    void tableNumberChanged();

private:
    QString m_newOrder;
    QString m_CallWaiter;
    QString m_name;
    QString m_order;
    int m_pieces;
    QString m_orderName;
    float m_price;
    bool m_ready;
    bool m_cancellation;

};

#endif // MYTABLES_H
