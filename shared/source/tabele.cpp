#include "table.h"
using namespace rotable;

//------------------------------------------------------------------------------

Table::~Table() {
  // Delete all orders
  qDeleteAll(_orders.begin(), _orders.end());
  _orders.clear(); // Clear map
}

//------------------------------------------------------------------------------

Table::Table(QObject *parent)
    : rotable::Client(parent), _change(false), _waiterIsNeeded(false) {
  _lastOrder = -1;
}

//------------------------------------------------------------------------------

void Table::updateOrder(rotable::Order *order) {
  // Check if order contains order
  if (_orders.contains(order->id())) {
    _orders.value(order->id())->updateOrder(order);
    delete order;
    emit tableChanged();
  } else
    addOrder(order);
  // Change are made, set change value on true
}

//------------------------------------------------------------------------------

void Table::updateTableStatus(const rotable::Table *table) {
  // Change value create
  bool change = false;

  // Check if something change
  if (_waiterIsNeeded != table->_waiterIsNeeded) {
    // Change so we set change
    change = true;
    _waiterIsNeeded = table->_waiterIsNeeded;
    emit waiterIsNeededChanged();
  }

  if (_isConnected != table->_isConnected) {
    // Change so we set change
    change = true;
    _isConnected = table->_isConnected;
    emit isConnectedChanged();
  }

  // We do logic OR
  _change = _change || change;
}

//------------------------------------------------------------------------------

QList<rotable::Order *> Table::orderList() { return _orders.values(); }

//------------------------------------------------------------------------------

bool Table::hasOrder(const int &orderId) const {
  if (_orders.contains(orderId))
    return true;
  return false;
}

//------------------------------------------------------------------------------

void Table::disconnectTable() {
  disconnect(this, &Table::tableChanged, 0, 0);
  disconnect(this, &Table::waiterIsNeededChanged, 0, 0);
  foreach (Order *order, _orders) { order->disconnectOrder(); }
}

//------------------------------------------------------------------------------

bool Table::isNewOrder() const {
  foreach (Order *order, _orders)
    if (order->isNew())
      return true;

  return false;
}

//------------------------------------------------------------------------------

QMap<int, QJsonValue> *Table::getOrderJSON() const {
  QMap<int, QJsonValue> *map = new QMap<int, QJsonValue>;
  foreach (Order *order, _orders) {
    if (order->change())
      map->insert(order->id(), order->toJSON());
  }
  return map;
}

//------------------------------------------------------------------------------

void Table::addAdditionalData(QJsonObject &obj) const {
  obj["connected"] = _isConnected;
  obj["waiterIsNeeded"] = _waiterIsNeeded;
}

//------------------------------------------------------------------------------

void Table::setAdditionalData(QJsonObject &obj) {
  _isConnected = obj["connected"].toBool();
  _waiterIsNeeded = obj["waiterIsNeeded"].toBool();
  _name = obj["name"].toString();
}

//------------------------------------------------------------------------------

void Table::recalcLastOrder() {
  // TODO: Warning, add check
  Order *sendOrder = reinterpret_cast<Order *>(sender());
  if (sendOrder->id() != _lastOrder && _lastOrder != -1)
    return;
  // Check orders on table, orders are sorted by id
  for (auto order = _orders.find(sendOrder->id()); order != _orders.end();
       ++order)
    // If order has status new
    if (order.value()->isNew()) {
      // Set id
      _lastOrder = order.value()->id();
      emit lastOrderChange();
      return; // End
    }
  // No find order, set -1
  if (_lastOrder != -1) {
    _lastOrder = -1;
    emit lastOrderChange();
  }
}

//------------------------------------------------------------------------------

void Table::diconnectRemote() { disconnectTable(); }

//------------------------------------------------------------------------------

void Table::prepareOrderToSend() { emit sendOrders(); }

//------------------------------------------------------------------------------

void Table::orderChanged() {
  _change = true;
  emit tableChanged();
}

//------------------------------------------------------------------------------

void Table::recalcOrderedProductsCount()
{
  _orderedProductCount = 0;
  for(auto order: _orders)
    _orderedProductCount += order->countProducts();
}

//------------------------------------------------------------------------------
