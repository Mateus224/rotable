#ifndef TABLE_H
#define TABLE_H
#include <QObject>
#include "orderinformation.h"

class table //: public QObject//, public OrderInformation
{
    //Q_OBJECT
    //Q_PROPERTY(int pieces READ tableNumber WRITE settableNumber NOTIFY tableNumberChanged)

public:
    table();//(QObject *parent=0);
    table(const int &tableNumber);//, QObject *parent=0);

    int tableNumber() const;
    void settableNumber(const int &tableNumber);
    QList <QObject*>  L_orderinformation;
    void add_orderinformation();
    void cancellation_orderinformation(int position);
    void ready_orderinformation(int position);

//signals:
    void tableNumberChanged();

private:
    int m_tableNumber;
};

#endif // TABLE_H
