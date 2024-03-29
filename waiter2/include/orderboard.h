#ifndef ROTABLE_ORDERBOARD_H
#define ROTABLE_ORDERBOARD_H

//-----------------------------------------------------

namespace rotable{
    class OrderBoard;
}

//-----------------------------------------------------

#ifndef QMAP_H
#include <QMap>
#endif

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QABSTRACTITEMMODEL_H
#include <QAbstractListModel>
#endif

#include <table.h>
#include "order.h"

//-----------------------------------------------------

class rotable::OrderBoard: public QAbstractListModel{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChange)
    Q_PROPERTY(double ordersPrice READ ordersPrice NOTIFY ordersPriceChange)
    Q_PROPERTY(bool isSomethingSelected READ isSomethingSelected WRITE setIsSomethingSelected NOTIFY isSomethingSelectedChanged)
public:

    //-----------------------------------------------------
    // Enum
    //-----------------------------------------------------

    /**
     * List with field (Roles)
     */
    enum BoardRoles {
        DateRole = Qt::UserRole + 1,
        StatusRole,
        ClientRole,
        OrderRole,
        ItemsRole,
        OrderPrice
    };

    //-----------------------------------------------------
    // Constructor and Destructor
    //-----------------------------------------------------

    /**
     * Default constructor
     * @param parent
     */
    OrderBoard(QObject *parent = 0);

    /**
    *  Default destructor
    */
    ~OrderBoard();

    //-----------------------------------------------------
    // Virtual method from QAbstractListModel
    //-----------------------------------------------------

    /**
    * Get number of item
    *
    * @param parent
    * @return               Number of item's(in _orders)
    */
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;

    /**
     * Get data in field
     *
     * @param index         index object(have number of row)
     * @param role          From enum (field name)
     * @return              QVariant with data
     */
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    /**
     * Method for add order to model
     *
     * @param order         Order object
     */
    void addOrder(rotable::Order *order);

    /**
     * Count of order in model
     *
     * @return  orders count
     */
    int count() const;

    Q_INVOKABLE void changeState(int state);

    inline bool isSomethingSelected() const { return _isSomethingSelect; }
    inline void setIsSomethingSelected(bool changed)
        { _isSomethingSelect = changed; emit isSomethingSelectedChanged(); }

    /**
     * Calculate price for all order on table
     *
     * @return      sum price
     */
    double ordersPrice() const;

protected:
    //-----------------------------------------------------
    // Virtual method from QAbstractListModel
    //-----------------------------------------------------

    /**
     * Method returns fields
     *
     * @return              QHash with fields name
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

signals:
    void countChange();
    void ordersPriceChange();
    void isSomethingSelectedChanged();
    void prepareOrderToSend();
    void disconnectNotification();
    void oldOrder(rotable::Order*);
    void unLoadTable();

public slots:
    /**
     * Read orders from table, used to update and load new order form table
     *
     * @param table         Table object
     */
    void readOrderFromTable(rotable::Table *table);

    /**
     * Update orders on table when table send signal
     */
    void updateOrders();

private slots:
    void orderReadyToChange(bool change);
    void clearBoard();

private:
    /**
     * Clear _orders QMap
     */

    inline void clearOrders();
    /**
     * load orders form specific table
     * @param table         Table object
     */
    void loadOrders(Table *table);

    void disconnectSignals();

    QMap<int, rotable::Order*> _orders;
    int _tableId;
    bool _isSomethingSelect;
    int _itemsSelect;
};

//-----------------------------------------------------

#endif // ROTABLE_ORDERBOARD_H

