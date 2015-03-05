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
    void readySlot(const bool &ready)
    {
        m_ready=ready;
        qDebug()<<"test";

    }

    void cancSlot(const bool &canc)
    {
        m_canc=canc;
        qDebug()<<"test2";
    }

    private:
    QQmlContext &ctxt;
    myTables* tab;


    public:
        int m_tableNumber;
        int m_ready;
        int m_canc;
};

#endif // QMLCONTEXT_H
