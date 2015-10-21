#include "orderboard.h"

//-----------------------------------------------------

using namespace rotable;

//-----------------------------------------------------

OrderBoard::OrderBoard(QObject *parent):
    QAbstractListModel(parent), _isSomethingSelect(false), _itemsSelect(0)
{

}

//-----------------------------------------------------

OrderBoard::~OrderBoard(){
    clearOrders();
}

//-----------------------------------------------------

void OrderBoard::addOrder(Order *order)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    if(order)
        _orders[order->id()] = order;
    else
        qCritical() << "Empty order object";
    endInsertRows();
    emit countChange();
}

//-----------------------------------------------------

int OrderBoard::count() const
{
    return _orders.count();
}

//-----------------------------------------------------

void OrderBoard::changeState(int state)
{
    foreach (Order *order, _orders) {
        order->changeState(state);
    }
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
    case OrderRole:{
        return QVariant(order->id());
    }break;
    case ItemsRole:{
        QList<QObject*> list;
        for(int i=0;i<order->itemCount();++i)
            list.append(order->item(i));
        return QVariant::fromValue(list);
    }break;
    }
}

//-----------------------------------------------------

void OrderBoard::readOrderFromTable(Table *table)
{
    //ToDo: add remove last connected signal for slot updateOrders
    //disconnect(updateOrders);
//    if(table->id()!=_tableId){
    // Clear connect signals
    emit diconnectTable();
    disconnect(this, &OrderBoard::diconnectTable, 0, 0);
    // Clear variable to activated button
    setIsSomethingSelected(false);
    _itemsSelect = 0;
    // Connect new Table with OrderBoard
    connect(table, &rotable::Table::tableChanged, this, &OrderBoard::updateOrders);
    connect(this, &OrderBoard::diconnectTable, table, &rotable::Table::diconnectRemote);
//    }

    loadOrders(table);
    _tableId=table->id();
}

//-----------------------------------------------------

void OrderBoard::updateOrders()
{
    Table *table = dynamic_cast<Table*>(QObject::sender());
    if(table)
      loadOrders(table);
    else
        qCritical() << "Someone call method, forbiden";
}

//-----------------------------------------------------

void OrderBoard::orderReadyToChange(bool change)
{
   if(change)
      ++_itemsSelect;
   else
       --_itemsSelect;
   setIsSomethingSelected(_itemsSelect);
}

//-----------------------------------------------------

QHash<int, QByteArray> OrderBoard::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[DateRole] = "orderDate";
    roles[StatusRole] = "orderStatus";
    roles[ClientRole] =  "clientId";
    roles[OrderRole] =  "orderId";
    roles[ItemsRole]  = "orderItems";

    return roles;
}

//-----------------------------------------------------

void OrderBoard::clearOrders()
{
    beginResetModel();
    _orders.clear();     //Clear list
    endResetModel();
}

//-----------------------------------------------------

void OrderBoard::loadOrders(rotable::Table *table)
{
    clearOrders();
    QList<rotable::Order *> orders = table->orderList();
    foreach (Order *order, orders) {
         addOrder(order);
         connect(order, &rotable::Order::readyToChanged, this, &OrderBoard::orderReadyToChange);
    }
}

//-----------------------------------------------------
