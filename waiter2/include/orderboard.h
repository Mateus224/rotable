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

#include "table.h"
#include "order.h"

//-----------------------------------------------------

class rotable::OrderBoard: public QAbstractListModel{
    Q_OBJECT
public:

    //-----------------------------------------------------
    // Enum
    //-----------------------------------------------------

    /**
     * List with field (Roles)
     */
    enum BoardRoles {
        TypeRole = Qt::UserRole + 1,
        SizeRole
    };

    //-----------------------------------------------------
    // Constructor and Destructor
    //-----------------------------------------------------

    /**
     * Default constructor
     * @param parent
     */
    OrderBoard(QObject *parent = 0);



    //-----------------------------------------------------
    // Virtual method from QAbstractListModel
    //-----------------------------------------------------

    /**
    * Get number of item
    *
    * @param parent
    * @return              Number of item's(in _orders)
    */
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    /**
     * Get data in field
     *
     * @param index         index object(have number of row)
     * @param role          From enum (field name)
     * @return              QVariant with data
     */
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


    /**
     * Method for add order to model
     *
     * @param order       Order object
     */
    void addOrder(const rotable::Order &order);

    /**
     * Read orders from table, used to update and load new order form table
     *
     * @param table       Table object
     */
    void readOrderFromTable(const rotable::Table &table);

protected:
    //-----------------------------------------------------
    // Virtual method from QAbstractListModel
    //-----------------------------------------------------

    /**
     * Method returns fields
     *
     * @return              QHash with fields name
     */
    QHash<int, QByteArray> roleNames() const;

private:
    QMap<int, rotable::Order> _orders;
    int _tableId;
};

//-----------------------------------------------------

#endif // ROTABLE_ORDERBOARD_H

