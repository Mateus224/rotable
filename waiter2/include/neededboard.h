#ifndef ROTABLE_NEEDEDBOARD_H
#define ROTABLE_NEEDEDBOARD_H

//-----------------------------------------------------

namespace rotable{
    class NeedBoard;
}

//-----------------------------------------------------

#ifndef QMAP_H
#include <QList>
#endif

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QABSTRACTITEMMODEL_H
#include <QAbstractListModel>
#endif

#include  "table.h"

//-----------------------------------------------------

class rotable::NeedBoard: public QAbstractListModel{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChange)
public:

    //-----------------------------------------------------
    // Enum
    //-----------------------------------------------------

    /**
     * List with field (Roles)
     */
    enum BoardRoles {
        NameRole = Qt::UserRole + 1,
    };

    //-----------------------------------------------------
    // Constructor and Destructor
    //-----------------------------------------------------

    /**
     * Default constructor
     *
     * @param parent
     */
    NeedBoard(QObject *parent = 0);

    /**
    *  Default destructor
    */
    ~NeedBoard();

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
     * Count of order in model
     *
     * @return  orders count
     */
    inline int count() const;

    /**
     * Remove Table from model, change state need to false
     *
     * @param idx           Table index
     */
    Q_INVOKABLE void unneedTable(int idx);

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
    void unsetWaiterNeed(int);

public slots:
    /**
     * Slot for read signal waiterIsNeededChanged
     * and analize waiterIsNeeded
     */
    void tableNeedChanged();

private :
    /**
     * Add table to model
     *
     * @param table         Table object
     */
    void addTable(rotable::Table *table);

    /**
     * Remove table from model
     *
     * @param table         Table object
     */
    void removeTable(Table *table);

    /**
     * List of tables
     */
    QList<rotable::Table*> _needs;
};

//-----------------------------------------------------

#endif // ROTABLE_NEEDEDBOARD_H

