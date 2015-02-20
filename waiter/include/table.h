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
    table(const int &tableNumber, QObject *parent=0);
    ~table() {}
    int tableNumber() const;
    void settableNumber(const int &tableNumber);

    void add_orderinformation();
    void cancellation_orderinformation(int position);
    void ready_orderinformation(int position);

    QList <QObject*>  L_orderinformation;

signals:
    void tableNumberChanged();

private:
    int m_tableNumber;
};

#endif // TABLE_H
