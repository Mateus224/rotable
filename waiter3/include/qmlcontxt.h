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
        void resetOldCurrentTable();
        void holdNewOrder();
        void addAllPrices();


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
            tableNumber.value(m_tableNumber)->setColor_orderinformation(index, "green");
        }
        else if(ready=="green")
        {
            tableNumber.value(m_tableNumber)->setColor_orderinformation(index, "black");
        }
    }

    void payedSlot()
    {
        tableNumber.value(m_tableNumber)->L_orderinformation.clear();
        contxt(m_tableNumber);
    }

    void cancSlot(const QString &canc, const int index)
    {
        if(canc=="black")
        {
            tableNumber.value(m_tableNumber)->setColor_orderinformation(index, "red");
            s_storno_prices thisPrice= {tableNumber.value(m_tableNumber)->L_orderinformation.value(index)->m_price,index};
            L_price.append(thisPrice);
            tableNumber.value(m_tableNumber)->L_orderinformation.value(index)->setprice(0);
            addAllPrices();
        }
        else if(canc=="red")
        {
            tableNumber.value(m_tableNumber)->setColor_orderinformation(index, "black");
            for(int i=0; i<L_price.length();i++)
            {
               if (L_price.value(i).s_index==index)
               {
                   tableNumber.value(m_tableNumber)->L_orderinformation.value(index)->setprice(L_price.value(i).s_price );
                   addAllPrices();
               }
            }
        }
    }

    private:
    QQmlContext &ctxt;
    myTables* tab;
    float _price;
    struct s_storno_prices{
        double s_price;
        int s_index;
    };
    QList <s_storno_prices> L_price;


    public:
        int m_tableNumber;
        QString m_ready;
        QString m_canc;
};

#endif // QMLCONTEXT_H
