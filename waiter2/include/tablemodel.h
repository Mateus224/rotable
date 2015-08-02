#ifndef ROTABLE_TABLEMODEL_H
#define ROTABLE_TABLEMODEL_H

//-----------------------------------------------------

namespace rotable{
    class TableModel;
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

//-----------------------------------------------------

class rotable::TableModel: public QAbstractListModel{

    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:

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
        OrderNumberRole
    };

    //-----------------------------------------------------
    // Constructor and Destructor
    //-----------------------------------------------------

    /**
     * Default constructor
     * @param parent
     */
    TableModel(QObject *parent = 0);

    /**
     * Default destructor
    */
    ~TableModel();

    //-----------------------------------------------------
    // Virtual method from QAbstractListModel
    //-----------------------------------------------------

    /**
     * Method returns fields
     *
     * @return              QHash with fields name
     */
    QHash<int, QByteArray> roleNames() const;

    /**
     * Get number of item
     *
     * @param parent
     * @return              Number of item's(in _tables)
     */
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    /**
     * Return number of column, in our case 1
     *
     * @param parent
     * @return              Number of column
     */
    int columnCount(const QModelIndex & parent = QModelIndex()) const;

    /**
     * Get data in field
     *
     * @param index         index object(have number of row)
     * @param role          From enum (field name)
     * @return              QVariant with data
     */
    QVariant data(const QModelIndex & index,
                  int role = Qt::DisplayRole) const;

    /**
     * We can implement that for screen rotation, etc. not implement
     *
     * @param section
     * @param orientation
     * @param role
     * @return
     */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    //-----------------------------------------------------
    // Method for manage tables
    //-----------------------------------------------------

    /**
     * Add table to model
     *
     * @param table         Table object
     */
    void addTable(rotable::Table *table);

    /**
     * Return number of tables in mode, use in Q_PROPERTY
     *
     * @return              count table
     */
    int count() const;

    rotable::Table *operator[]( int& idx);

    rotable::Table *at(const std::size_t &id);

signals:
    /**
     * Signal emiteed when count of table change
     */
    void countChanged();

private:
    /**
     * Container with tables
     */
    QMap<int, rotable::Table*> _tables;
};

#endif // ROTABLE_TABLEMODEL_H

