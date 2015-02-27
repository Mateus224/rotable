#ifndef QMLCONTEXT_H
#define QMLCONTEXT_H
#include <QObject>
#include <QList>
#include <qqmlcontext.h>
#include "../include/mytables.h"
#include "../include/orderinformation.h"


class qmlContxt: public QObject
{
    Q_OBJECT

    public:

        qmlContxt(QObject *parent=0);
        qmlContxt(QQmlContext &qmlCon, QObject *parent=0);


        //~qmlContxt();
        void contxt(int tableNr);
        void initContxt(int NumberOfTables);
        void add_orderInfoForTable(int tableNr,int pices,QString OrderName, float price);
        QList<myTables*> tableNumber;
public slots:
    void tableSlot(const int &msg) {
            m_tableNumber=msg-1;
            tableNumber.at(m_tableNumber)->setCallWaiter("Black");
            tableNumber.at(m_tableNumber)->setNewOrder("Transparent");
            contxt(m_tableNumber);
            tableNumber.at(m_tableNumber)->settableNumber(2);
        }

    private:
    QQmlContext &ctxt;

    myTables* tab;

    public:
        int m_tableNumber;
};

#endif // QMLCONTEXT_H
