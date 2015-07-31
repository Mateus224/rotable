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

class TableModel: public QAbstractListModel{

    Q_OBJECT

public:
    enum TableRoles {
        NameRole = Qt::UserRole + 1,
        ChangeRole,
        IdRole,
        WaiterNeedRole,
        OrderNumberRole
    };

    TableModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    int columnCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index,
                  int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
private:
    QMap _tables;
};

#endif // ROTABLE_TABLEMODEL_H

