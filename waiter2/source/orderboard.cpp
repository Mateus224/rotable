#include "orderboard.h"
#include <QtGui>


//-----------------------------------------------------

using namespace rotable;

//-----------------------------------------------------

OrderBoard::OrderBoard(QObject *parent):
    QAbstractListModel(parent), _isSomethingSelect(false), _itemsSelect(0)
{
    connect(this, &OrderBoard::prepareOrderToSend, this, &OrderBoard::clearBoard);
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
    emit prepareOrderToSend();
//    clearBoard();
//    emit unLoadTable();
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
        {
            if(!order->item(i)->isDone())
                list.append(order->item(i));
        }
        return QVariant::fromValue(list);
    }break;
    case OrderPrice:{
        return QVariant(QString("%1").arg(order->toPay()));
    }break;
    }
    return QVariant();
}

//-----------------------------------------------------

void OrderBoard::readOrderFromTable(Table *table)
{
    // If we want load this same table don't allow that
    if(_tableId == table->id())
        return;

    //ToDo: add remove last connected signal for slot updateOrders
    clearBoard();
    // Connect new Table with OrderBoard
    connect(table, &rotable::Table::tableChanged, this, &OrderBoard::updateOrders);
    connect(this, &OrderBoard::disconnectNotification, table, &rotable::Table::diconnectRemote);
    connect(this, &OrderBoard::prepareOrderToSend, table, &rotable::Table::prepareOrderToSend);

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

void OrderBoard::clearBoard()
{
    beginResetModel();
    // Clear connect signals
    disconnectSignals();
    // Clear variable to activated button
    setIsSomethingSelected(false);
    _itemsSelect = 0;

    clearOrders();

    _tableId = -1;
    endResetModel();
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
    roles[OrderPrice] = "orderPrice";

    return roles;
}

//-----------------------------------------------------

double OrderBoard::ordersPrice() const
{
    double sum = 0;

    foreach (Order *order, _orders) {
        sum += order->toPay();
    }

    return sum;
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
         if(order->isClose()){
             emit  oldOrder(order);
             continue;
         }
         else if (!order->isUnDone()) {
             emit  oldOrder(order);
         }
         addOrder(order);
         connect(order, &rotable::Order::readyToChanged, this, &OrderBoard::orderReadyToChange);
         connect(this, &OrderBoard::disconnectNotification, order, &rotable::Order::disconnectOrder);
    }
    emit ordersPriceChange();
}

//-----------------------------------------------------

void OrderBoard::disconnectSignals()
{
    emit disconnectNotification();

    disconnect(this,&OrderBoard::prepareOrderToSend, 0, 0);
    disconnect(this, &OrderBoard::disconnectNotification, 0, 0);
}

//-----------------------------------------------------
