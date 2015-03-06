#ifndef QMLCONTEXT_H
#define QMLCONTEXT_H
#include <QObject>
#include <QList>
#include <qqmlcontext.h>
#include "../include/mytables.h"
#include "../include/orderinformation.h"
#include "../include/waiterappwindow.h"

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
        void resetOldCurrentTable();
        void holdNewOrder();
        void addAllPrices();

        WaiterAppWindow* AppWindow;
        QList<myTables*> tableNumber;

public slots:
    void tableSlot(const int &msg) {

        m_tableNumber=msg-1;
        resetOldCurrentTable();
        tableNumber.at(m_tableNumber)->setCallWaiter("Black");
        tableNumber.at(m_tableNumber)->setNewOrder("Transparent");
        contxt(m_tableNumber);
        tableNumber.at(m_tableNumber)->settableNumber("Lightblue");
        addAllPrices();
        holdNewOrder();
        }
    void readySlot(const QString &ready, const int &index)
    {
        if(ready=="black")
        {
            tableNumber.at(m_tableNumber)->setColor_orderinformation(index, "green");
        }
        else if(ready=="green")
        {
            tableNumber.at(m_tableNumber)->setColor_orderinformation(index, "black");
        }
    }

    void cancSlot(const QString &canc, const int index)
    {
        if(canc=="black")
        {
            tableNumber.at(m_tableNumber)->setColor_orderinformation(index, "red");
        }
        else if(canc=="red")
        {
            tableNumber.at(m_tableNumber)->setColor_orderinformation(index, "black");
        }
    }

    private:
    QQmlContext &ctxt;
    myTables* tab;


    public:
        int m_tableNumber;
        QString m_ready;
        QString m_canc;
};

#endif // QMLCONTEXT_H
