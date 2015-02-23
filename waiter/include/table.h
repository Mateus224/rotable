#ifndef TABLE_H
#define TABLE_H
#include <QObject>
#include "orderinformation.h"

class table : public QObject//, public OrderInformation
{
    Q_OBJECT
   // Q_PROPERTY(int pieces READ tableNumber WRITE settableNumber NOTIFY tableNumberChanged)

public:
    table(QObject *parent=0);
    table(const int &tableNumber, const QString &name, const QString &order, const int &pieces,const QString &orderName,
                                 const float &price, const bool &ready, const bool &cancellation,  QObject *parent=0);
    ~table() {}
    int tableNumber() const;
    void settableNumber(const int &tableNumber);

    void add_orderinformation(const QString m_name,const QString m_order, const int m_pieces,const QString m_orderName,const float m_price,const bool m_ready,const bool m_cancellation);
    void cancellation_orderinformation(int position);
    void ready_orderinformation(int position);

    QList <OrderInformation*>  L_orderinformation;

    int m_tableNumber;
public slots:
    void tableSlot(const int &msg) {
            qDebug() << "Message from table nr.:" << msg;
            m_tableNumber=msg;
        }
signals:
    void tableNumberChanged();

private:

    QString m_name;
    QString m_order;
    int m_pieces;
    QString m_orderName;
    float m_price;
    bool m_ready;
    bool m_cancellation;
};

#endif // TABLE_H
