#include "tablemodel.h"

//-----------------------------------------------------

using rotable::Table;
using rotable::TableModel;

//-----------------------------------------------------

TableModel::TableModel(QObject *parent): QAbstractListModel(parent)
{

}

//-----------------------------------------------------

TableModel::~TableModel()
{
    qDeleteAll(_tables.begin(), _tables.end());
    _tables.clear();     //Clear list
}

//-----------------------------------------------------

QHash<int, QByteArray> TableModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[NameRole] = "name";
    roles[ChangeRole] = "change";
    roles[IdRole] = "id";
    roles[WaiterNeedRole] = "waiterNeeded";
    roles[OrderNumberRole] = "orderNumber";
    return roles;
}

//-----------------------------------------------------

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
      return 0;
    } else {
        return _tables.size();
    }
}

//-----------------------------------------------------

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

//-----------------------------------------------------

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (index.column() == 0) {
        if(_tables.count()>=index.row())
            return QVariant();
        Table *table = _tables[_tables.keys()[index.row()]];
        switch (role) {
        case NameRole:{
            return QVariant(table->name());
        }break;
        case ChangeRole:{
            //return QVariant(table->isStatusChange());
        }break;
        case IdRole:{
            return QVariant(table->id());
        }break;
        case WaiterNeedRole:{
            //return QVariant(table->isWaiterNeeded());
        }break;
        case OrderNumberRole:{
            return QVariant(table->orderCount());
        }break;
        }
    }
    return QVariant();
}

//-----------------------------------------------------

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
      if (section == 0) {
        return QVariant(tr("Name"));
      }
    }

    return QVariant();
}

//-----------------------------------------------------

int TableModel::count() const
{
    return _tables.count();
}

//-----------------------------------------------------

void TableModel::addTable(rotable::Table *table)
{
    if(_tables.contains(table->id()))
    {
        _tables[table->id()]->updateTableStatus(table);
    }
    else
    {
        _tables[table->id()] = table;
        emit countChanged();
    }
}

//-----------------------------------------------------

rotable::Table *rotable::TableModel::operator[]( int& idx)
{
    return _tables[idx];
}

//-----------------------------------------------------

rotable::Table *rotable::TableModel::at(const std::size_t &id)
{
    if(_tables.contains(id))
        return _tables[id];
    else
        NULL;
}

//-----------------------------------------------------
