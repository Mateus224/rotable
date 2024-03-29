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

#include <table.h>

//-----------------------------------------------------

class rotable::TableModel: public QAbstractListModel{

    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int selectTable READ selectTable WRITE setSelectTable NOTIFY selectTableChanged)
    Q_PROPERTY(double income READ income NOTIFY incomeChanged)
    Q_PROPERTY(QString incomeStr READ incomeStr NOTIFY incomeChanged)

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
        OrderNumberRole,
        ConnectedRole,
        SelectRole
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

protected:
    /**
     * Method returns fields
     *
     * @return              QHash with fields name
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

public:
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

    //-----------------------------------------------------
    // Method for manage tables
    //-----------------------------------------------------

    /**
     * Add table to model
     *
     * @param table         Table object
     */
    bool addTable(rotable::Table *table);

    /**
     * Return number of tables in mode, use in Q_PROPERTY
     *
     * @return              count table
     */
    int count() const;

    /**
     * Override operator [], for easier use, not work propety but it should
     * @param id            table Id
     * @return              Tabele pointer, or null if table not exists
     */
    rotable::Table *operator[](const std::size_t& id);

    /**
     * Get table
     * @param id            table id
     * @return              Tabele pointer, or null if table not exists
     */
    rotable::Table *at(const std::size_t &id);

    /**
     * Add/Update order in table
     *
     * @param tableId       table id
     * @param order         order object
     * @return              true  on success(false e.i. table doesn't exists)
     */
    bool updateOrder(const int &tableId, rotable::Order *order);

    /**
     * Update field WaiterIsNeeded in table object
     * @param need          value of field
     * @param tableId       id of table
     * @return              true on success
     */
    bool updateWaiterIsNeed(const bool &need, const int &tableId);

    /**
     * Send orders to
     * @param tableId
     */
    Q_INVOKABLE void sendToBoardOrder(int tableId);

    inline int selectTable() const { return _selectTable;}
    void setSelectTable(const int &selectTable);

    inline double income() const{ return _income;}
    inline QString incomeStr() const{ return QString("%1").arg(QString::number(_income, 'q', 2));}
    void setIncome(double income){ _income = income; emit incomeChanged(); }

signals:
    /**
     * Signal for update OrderBoard
     * @param table
     */
    void updateOrderBoard(rotable::Table* table);

    void countChanged();
    void selectTableChanged();

    void sendToHistory(rotable::Order* order);
    void incomeChanged();

public slots:
    void unLoadTable();

private slots:
    /**
     * Method sort table and return list with id's
     *
     * @return  QList with id's
     */
    void sortTableKeys();

private:
    /**
     * Container with tables
     */
    QMap<int, rotable::Table*> _tables;

    /**
     * Contains ids of table base on order of new orders
     */
    QList<int> _orderList;
    double _income;
    int _selectTable;
};

#endif // ROTABLE_TABLEMODEL_H

