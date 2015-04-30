#ifndef QMLCONTEXT_H
#define QMLCONTEXT_H
#include <QObject>
#include <QList>
#include <qqmlcontext.h>
#include "../include/mytables.h"
#include "../include/orderinformation.h"
#include "../../waiter/include/waiterappwindow.h"

class qmlContxt: public QObject
{
    Q_OBJECT

    public:

        qmlContxt(QObject *parent=0);
        qmlContxt(QQmlContext &qmlCon, QObject *parent=0);


        /**
         * @brief contxt
         * @param tableNr
         * sets the context between C++ and QML
         */
        void contxt(int tableNr);

        /**
         * @brief initContxt
         * @param NumberOfTables
         * Setting the
         */
        void initContxt(int NumberOfTables);
        void add_orderInfoForTable(int tableNr,int pices,QString OrderName, float price);
        void resetOldCurrentTable();
        void holdNewOrder();
        void addAllPrices();

        WaiterAppWindow* AppWindow;
        QList<myTables*> tableNumber;

public slots:
        /**
     * @brief tableSlot
     * @param msg
     * Setting in the Waitor Gui the colors
     */
    void tableSlot(const int &msg);

    /**
     * @brief readySlot
     * @param ready
     * @param index
     * If the Waitor clicked the button "check"
     * it sets the colors of that table to this color
     */
    void readySlot(const QString &ready, const int &index);

    /**
     * @brief payedSlot
     * if the Waitor clicked the button "payed" we clear
     * the orderlist
     */
    void payedSlot();

    /**
     * @brief cancSlot
     * @param canc
     * @param index
     * This funktion magaget the cancelation of the Waitor don't
     * can make this drink
     */
    void cancSlot(const QString &canc, const int index);

    private:
    QQmlContext &ctxt;
    myTables* tab;
    float _price;

    /**
     * @brief The s_storno_prices struct
     * we need this struckt know in which index is the
     * the canceled order
     */
    struct s_storno_prices{
        double s_price;
        int s_index;
    };

    /**
     * @brief L_price
     * Here we store the canceled orders
     */
    QList <s_storno_prices> L_price;


    public:
        int m_tableNumber;
        QString m_ready;
        QString m_canc;
};

#endif // QMLCONTEXT_H
