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
    Q_UNUSED(parent);
    return _tables.count();
}

//-----------------------------------------------------

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= _tables.count())
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
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        _tables[table->id()] = table;
        endInsertRows();
    }
}

//-----------------------------------------------------

rotable::Table *rotable::TableModel::operator[](const std::size_t& id)
{
    if(_tables.contains(id))
        return _tables[id];
    else
        return NULL;
}

//-----------------------------------------------------

rotable::Table *rotable::TableModel::at(const std::size_t &id)
{
    if(_tables.contains(id))
        return _tables[id];
    else
        return NULL;
}

//-----------------------------------------------------

void TableModel::sendOrderFromTable(int tableId)
{
    emit updateOrderBoard(*_tables[tableId]);
}

//-----------------------------------------------------
