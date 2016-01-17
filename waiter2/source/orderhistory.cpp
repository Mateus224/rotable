#include "orderhistory.h"

using rotable::OrderHistory;

//-----------------------------------------------------

OrderHistory::OrderHistory(QObject *parent): QAbstractListModel(parent)
{

}

//-----------------------------------------------------

int OrderHistory::rowCount(const QModelIndex &parent) const
{
    return 0;
}

//-----------------------------------------------------

QVariant OrderHistory::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

//-----------------------------------------------------

void OrderHistory::reciveOrder(rotable::Order *order)
{
    if(!_list.contains(order->id()))
    {
        _list.insert(order->id(), order);
        // TODO: add update model
    }
}

//-----------------------------------------------------

QHash<int, QByteArray> OrderHistory::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[NameRole] = "name";
    roles[ChangeRole] = "change";
    roles[IdRole] = "id";
    roles[WaiterNeedRole] = "waiterNeeded";
    roles[OrderNumberRole] = "orderNumber";
    roles[ConnectedRole] = "isConnected";
    return roles;
}

//-----------------------------------------------------
