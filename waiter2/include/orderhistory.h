#ifndef ROTABLE_ORDERHISTORY_H
#define ROTABLE_ORDERHISTORY_H

//-----------------------------------------------------

namespace rotable{
    class OrderHistory;
}

//-----------------------------------------------------

#ifndef QMAP_H
#include <QMap>
#endif

#ifndef QSTRING_H
#include <QString>
#endif

#include <QAbstractListModel>

#include "order.h"

class rotable::OrderHistory : public QAbstractListModel
{
    Q_OBJECT

public slots:
    void reciveOrder(rotable::Order *order);

public:
    OrderHistory(QObject *parent = NULL);

    //-----------------------------------------------------
    // Enum
    //-----------------------------------------------------

    /**
     * List with field (Roles)
     */
    enum TableRoles {
        NameRole = Qt::UserRole + 1,
        ChangeRole,
        IdRole,
        WaiterNeedRole,
        OrderNumberRole,
        ConnectedRole
    };

    //-----------------------------------------------------
    // Virtual method from QAbstractListModel
    //-----------------------------------------------------

    /**
     * Get number of item
     *
     * @param parent
     * @return              Number of item's(in _tables)
     */
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;

    /**
     * Get data in field
     *
     * @param index         index object(have number of row)
     * @param role          From enum (field name)
     * @return              QVariant with data
     */
    QVariant data(const QModelIndex & index,
                  int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

protected:
    /**
     * Method returns fields
     *
     * @return              QHash with fields name
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

private:
    QMap<int, rotable::Order*> _list;
};

#endif // ORDERHISTORY_H
