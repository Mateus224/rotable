#include "tablemodel.h"
#include <QtGui>

//-----------------------------------------------------

using rotable::Table;
using rotable::TableModel;

//-----------------------------------------------------

TableModel::TableModel(QObject *parent)
    : QAbstractListModel(parent), _selectTable(0) {
  _income = 0;
}

//-----------------------------------------------------

TableModel::~TableModel() {
  qDeleteAll(_tables.begin(), _tables.end());
  _tables.clear(); // Clear list
}

//-----------------------------------------------------

void TableModel::clearOrders() {
      foreach (Table *table, _tables) {
          table->_orders.clear();
      }

    //_orderList.clear();
    beginResetModel();
    endResetModel();
}

//-----------------------------------------------------

QHash<int, QByteArray> TableModel::roleNames() const {
  QHash<int, QByteArray> roles;

  roles[NameRole] = "name";
  roles[ChangeRole] = "isChange";
  roles[IdRole] = "id";
  roles[WaiterNeedRole] = "waiterNeeded";
  roles[OrderNumberRole] = "orderNumber";
  roles[ConnectedRole] = "isConnected";
  roles[SelectRole] = "isSelected";
  roles[CountInc] = "incomingCount";
  return roles;
}

//-----------------------------------------------------

void TableModel::sortTableKeys() {
  QMap<int, int> map;  // For ids to sort
  QList<int> listDone; // Store table withwout new orders
  foreach (Table *table, _tables) {
    if (table->lastOrderId() == -1)
      listDone.append(table->id());
    else
      map.insert(table->lastOrderId(), table->id());
  }

  _orderList.clear();
  _orderList.append(map.values());
  _orderList.append(listDone);
}

//-----------------------------------------------------

int TableModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return _tables.count();
}

//-----------------------------------------------------

QVariant TableModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() > _tables.count())
    return QVariant();

  Table *table = _tables[_orderList[index.row()]];
  switch (role) {
  case NameRole: {
    return QVariant(table->name());
  } break;
  case ChangeRole: {
    return QVariant(table->isNewOrder());
  } break;
  case IdRole: {
    return QVariant(table->id());
  } break;
  case WaiterNeedRole: {
    // return QVariant(table->isWaiterNeeded());
  } break;
  case OrderNumberRole: {
    return QVariant(table->orderCount());
  } break;
  case ConnectedRole: {
    return QVariant(table->isConnected());
  } break;
  case SelectRole: {
    return QVariant(table->id() == _selectTable);
  } break;
  case CountInc: {
    return QVariant(table->getincomingOrderCount());
  } break;
  default: { return QVariant(); } break;
  }
  return QVariant();
}

//-----------------------------------------------------

int TableModel::count() const { return _tables.count(); }

//-----------------------------------------------------

bool TableModel::addTable(rotable::Table *table) {
  if (_tables.contains(table->id())) {
    beginResetModel();
    _tables[table->id()]->updateTableStatus(table);
    endResetModel();

    return false;
  } else {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _tables[table->id()] = table;
    connect(table, &rotable::Table::lastOrderChange, this,
            &rotable::TableModel::sortTableKeys);
    emit table->lastOrderChange();
    endInsertRows();

    return true;
  }
}

//-----------------------------------------------------

rotable::Table *rotable::TableModel::operator[](const std::size_t &id) {
  if (_tables.contains(id))
    return _tables[id];
  else
    return NULL;
}

//-----------------------------------------------------

rotable::Table *rotable::TableModel::at(const std::size_t &id) {
  if (_tables.contains(id))
    return _tables[id];
  else
    return NULL;
}

//-----------------------------------------------------

bool TableModel::updateOrder(const int &tableId, rotable::Order *order) {
  // Check if we have specific table
  if (!_tables.contains(tableId)) {
    qDebug() << "Table with id " + QString(tableId) + " doesn't exists";
    return false; // If no return false
  }

  // Access to table
  Table *table = _tables[tableId];

  //    //Check if we have close order
  //    if(order->isClose())
  //    {
  //        // Use signal to send order
  //        sendToHistory(order);
  //        //return true;    // End
  //    }

  // Inform model somethiong will be change
  beginResetModel();
  // Check if order exists
  if (table->hasOrder(order->id()))
    table->updateOrder(order); // Update order
  else {
    if (order->isClose())
      // TODO: Change
      order->deleteLater();
    else
      table->addOrder(order); // Add order
  }
  endResetModel(); // End modify model

  return true; // Everything goes alright, return true
}

//-----------------------------------------------------

bool TableModel::updateWaiterIsNeed(const bool &need, const int &tableId) {
  if (!_tables.contains(tableId))
    return false;

  _tables[tableId]->setwaiterIsNeedede(need);
  return true;
}

//-----------------------------------------------------

void TableModel::sendToBoardOrder(int tableId) {

  setSelectTable(tableId);

  emit updateOrderBoard(_tables[tableId]);
}

//-----------------------------------------------------

void TableModel::setSelectTable(const int &selectTable) {
  beginResetModel();
  _selectTable = selectTable;
  emit selectTableChanged();
  endResetModel();
}

//-----------------------------------------------------

void TableModel::unLoadTable() { setSelectTable(-1); }

//-----------------------------------------------------
