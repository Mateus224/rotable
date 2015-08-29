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

    Q_PROPERTY(int count READ count)
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
        ItemsRole
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
    * @return              Number of item's(in _orders)
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
     * @param order       Order object
     */
    void addOrder(rotable::Order *order);

    int count(){
        return _orders.count();
    }

public slots:
    /**
     * Read orders from table, used to update and load new order form table
     *
     * @param table       Table object
     */
    void readOrderFromTable(rotable::Table &table);

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

private:
    QMap<int, rotable::Order*> _orders;
    int _tableId;
};

//-----------------------------------------------------

#endif // ROTABLE_ORDERBOARD_H

