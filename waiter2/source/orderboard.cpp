#include "orderboard.h"

//-----------------------------------------------------

using namespace rotable;

//-----------------------------------------------------

OrderBoard::OrderBoard(QObject *parent): QAbstractListModel(parent)
{

}

//-----------------------------------------------------

OrderBoard::~OrderBoard(){
    qDeleteAll(_orders.begin(), _orders.end());
    _orders.clear();     //Clear list
}

//-----------------------------------------------------

void OrderBoard::addOrder(Order *order)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _orders[order->id()] = order;
    endInsertRows();
}

//-----------------------------------------------------

int OrderBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _orders.count();
}

//-----------------------------------------------------

QVariant OrderBoard::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= _orders.count())
        return QVariant();


    Order *order = _orders[_orders.keys()[index.row()]];
    switch (role) {
    case DateRole:{
//        return QVariant(order->);
    }break;
    case StatusRole:{
//        return QVariant(order->);
    }break;
    case ClientRole:{
        return QVariant(order->clientId());
    }break;
    case ItemsRole:{
        QList<QObject*> list;
        for(int i=0;i<order->itemCount();++i)
            list << order->item(i);
        return QVariant::fromValue(list);
    }break;
    }
}

//-----------------------------------------------------

void OrderBoard::readOrderFromTable(Table &table)
{
    if(table.id()==_tableId)
    {
        //ToDo: Update order
    }
    else
    {
        beginResetModel();
        _orders.clear();
        endResetModel();
        QList<rotable::Order *> orders = table.orderList();
        foreach (Order *order, orders) {
             addOrder(order);
        }
        _tableId=table.id();
    }
}

//-----------------------------------------------------

QHash<int, QByteArray> OrderBoard::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[DateRole] = "date";
    roles[StatusRole] = "status";
    roles[ClientRole] =  "id";
    roles[ItemsRole]  = "orderItems";

    return roles;
}

//-----------------------------------------------------
