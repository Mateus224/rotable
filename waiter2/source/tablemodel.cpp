#include "tablemodel.h"

//-----------------------------------------------------

using rotable::TableModel;
using rotable::Table;

//-----------------------------------------------------

TableModel::TableModel(QObject *parent): QObject(parent)
{

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
