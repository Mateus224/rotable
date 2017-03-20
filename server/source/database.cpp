#include "private/precomp.h"

#include "database.h"
#include "order.h"
#include "settings.h"

#include <QDate>
#include <QSqlDriver>
#include <QSqlRecord>

//------------------------------------------------------------------------------
// For debug class with error for not implemented code

class NotImplementedException //: public std::logic_error
{
public:
  NotImplementedException() {} //: logic_error("Not implemented yet.") {}
};

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

static const char S_deleteProductsOfCategory[] =
    "DELETE FROM `%1products` WHERE `category_id` = %2;";

//------------------------------------------------------------------------------

Database::Database(QObject *parent) : QObject(parent), _connected(false) {

  SqlCommands categoryCmds;
  collectSqlCommands(categoryCmds, "categories");
  _sqlCommands.append(categoryCmds);

  SqlCommands productCmds;
  collectSqlCommands(productCmds, "products");
  _sqlCommands.append(productCmds);

  SqlCommands clientCmds;
  collectSqlCommands(clientCmds, "clients");
  _sqlCommands.append(clientCmds);

  SqlCommands orderCmds;
  collectSqlCommands(orderCmds, "orders");
  _sqlCommands.append(orderCmds);

  SqlCommands orderItemCmds;
  collectSqlCommands(orderItemCmds, "orderitems");
  _sqlCommands.append(orderItemCmds);

  SqlCommands incomeCmds;
  collectSqlCommands(incomeCmds, "incomes");
  _sqlCommands.append(incomeCmds);

  SqlCommands configCmds;
  collectSqlCommands(configCmds, "configs");
  _sqlCommands.append(configCmds);

  SqlCommands passwordCmds;
  collectSqlCommands(passwordCmds, "passwords");
  _sqlCommands.append(passwordCmds);

  SqlCommands macAdressCmds;
  collectSqlCommands(macAdressCmds, "macadresses");
  _sqlCommands.append(macAdressCmds);

  SqlCommands tablesDetailsCmds;
  collectSqlCommands(tablesDetailsCmds, "tabledetails");
  _sqlCommands.append(tablesDetailsCmds);

  SqlCommands mediaCmds;
  collectSqlCommands(mediaCmds, "medias");
  _sqlCommands.append(mediaCmds);

  SqlCommands advertisingVideoCMD;
  collectSqlCommands(advertisingVideoCMD, "advertisingvideos");
  _sqlCommands.append(advertisingVideoCMD);

  SqlCommands waiterCategoriesCmds;
  collectSqlCommands(waiterCategoriesCmds, "waitercategories");
  _sqlCommands.append(waiterCategoriesCmds);

  SqlCommands systemUpdateCmds;
  collectSqlCommands(systemUpdateCmds, "systemupdate");
  _sqlCommands.append(systemUpdateCmds);

  SqlCommands AdvertisingConfigCmds;
  collectSqlCommands(AdvertisingConfigCmds, "advertisingconfigs");
  _sqlCommands.append(AdvertisingConfigCmds);
  qDebug() << "Sql commands load succesfull";
}

//------------------------------------------------------------------------------

bool Database::startConnection(const QString &driver, const QString &host,
                               const QString &database, const QString &user,
                               const QString &pass, const QString &prefix) {
  _db = QSqlDatabase::addDatabase(driver);
  if (!_db.isValid()) {
    qDebug() << tr("Could not add '%1' database!").arg(driver);
    _connected = false;
    return false;
  }

  _db.setHostName(host);
  _db.setDatabaseName(database);
  _db.setUserName(user);
  _db.setPassword(pass);

  _prefix = prefix;

  _connected = _db.open() && _db.isValid();

  return _connected;
}

//------------------------------------------------------------------------------

bool Database::categoryIds(QList<int> &ids) {
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Categories]._listIds.arg(_prefix);

  QSqlQuery q(_db);
  // q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  while (q.next()) {
    bool toIntOk;
    ids << q.value("id").toInt(&toIntOk);
    if (!toIntOk) {
      qCritical() << tr("Could not convert entry '%1' to an integer!")
                         .arg(q.value("id").toString());
      ids.clear();
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::productIds(QList<int> &ids, int categoryId) {
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr;
  if (categoryId == -1) {
    queryStr = _sqlCommands[Products]._listIds.arg(_prefix);
  } else {
    queryStr = _sqlCommands[Products]
                   ._select.arg(_prefix, "`id`", "category_id")
                   .arg(categoryId);
  }

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  while (q.next()) {
    bool toIntOk;
    ids << q.value("id").toInt(&toIntOk);
    if (!toIntOk) {
      qCritical() << tr("Could not convert entry '%1' to an integer!")
                         .arg(q.value("id").toString());
      ids.clear();
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::orderIds(QList<int> &ids, int clientId) {
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr;
  if (clientId == -1) {
    queryStr = _sqlCommands[Orders]._listIds.arg(_prefix);
  } else {
    queryStr = _sqlCommands[Orders]
                   ._select.arg(_prefix, "`id`", "client_id")
                   .arg(clientId);
  }

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  while (q.next()) {
    bool toIntOk;
    ids << q.value("id").toInt(&toIntOk);
    if (!toIntOk) {
      qCritical() << tr("Could not convert entry '%1' to an integer!")
                         .arg(q.value("id").toString());
      ids.clear();
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::configIds(QList<int> &ids) {
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Configs]._listIds.arg(_prefix);
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  while (q.next()) {
    bool toIntOk;
    ids << q.value("id").toInt(&toIntOk);
    if (!toIntOk) {
      qCritical() << tr("Could not convert entry '%1' to an integer!")
                         .arg(q.value("id").toString());
      ids.clear();
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::orderItemIds(QList<int> &ids, int orderId) {
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[OrderItems]._select.arg(
      _prefix, "`id`", "order_id", ":order_id");
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":order_id", orderId);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  while (q.next()) {
    bool toIntOk;
    ids << q.value("id").toInt(&toIntOk);
    if (!toIntOk) {
      qCritical() << tr("Could not convert entry '%1' to an integer!")
                         .arg(q.value("id").toString());
      ids.clear();
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::orderItemIds(QList<int> &ids, int orderId, Waiter *waiterObj)
{
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr = "SELECT %1order_items.id FROM %1order_items,%1products WHERE %1order_items.order_id = %2 and %1order_items.product_id = %1products.id and %1products.category_id in (%3);";
  QString waiterStr;
  if(!waiterObj->categories())
    return true;
  for(auto id : *(waiterObj->categories()))
  {
    waiterStr += QString::number(id) + ",";
  }
  waiterStr.chop(1);
  queryStr = queryStr.arg(_prefix, ":order_id", waiterStr);
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":order_id", orderId);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  while (q.next()) {
    bool toIntOk;
    ids << q.value("id").toInt(&toIntOk);
    if (!toIntOk) {
      qCritical() << tr("Could not convert entry '%1' to an integer!")
                         .arg(q.value("id").toString());
      ids.clear();
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::clientIds(QList<int> &ids, int userType) {
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Clients]._select.arg(_prefix, "`id`", "type", ":type");
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":type", userType);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  while (q.next()) {
    bool toIntOk;
    ids << q.value("id").toInt(&toIntOk);
    if (!toIntOk) {
      qCritical() << tr("Could not convert entry '%1' to an integer!")
                         .arg(q.value("id").toString());
      ids.clear();
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::userIds(QList<int> &ids) {
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Clients]._select.arg(
      _prefix, "`id`", "type", ":type or type = :type2");
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":type", 0);
  q.bindValue(":type2", 2);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  while (q.next()) {
    bool toIntOk;
    ids << q.value("id").toInt(&toIntOk);
    if (!toIntOk) {
      qCritical() << tr("Could not convert entry '%1' to an integer!")
                         .arg(q.value("id").toString());
      ids.clear();
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::mediaIds(QList<int> &ids, int removed) {
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Medias]._listIds.arg(_prefix,"removed").arg(removed);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }
    //q.bindValue(":removed",removed);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  while (q.next()) {
    bool toIntOk;
    ids << q.value("id").toInt(&toIntOk);
    if (!toIntOk) {
      qCritical() << tr("Could not convert entry '%1' to an integer!")
                         .arg(q.value("id").toString());
      ids.clear();
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::typefileIds(QList<int> &ids, int type)
{
    //take the media ids which have the advertising type and take the info from advertising table

}

//------------------------------------------------------------------------------

ProductCategory *Database::category(int id) {
  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[Categories]._select.arg(_prefix, "*", "id").arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }

  bool ok;
  int category_id = q.value("id").toInt(&ok);
  if (!ok) {
    qDebug() << tr("Could not convert '%1' to integer!")
                    .arg(q.value("id").toString());
    return 0;
  }

  int sequence = q.value("sequence").toInt(&ok);
  if (!ok) {
    qDebug() << tr("Could not convert '%1' to integer!")
                    .arg(q.value("sequence").toString());
    return 0;
  }

  ProductCategory *c = new ProductCategory();
  c->setName(q.value("name").toString());
  c->setIcon(q.value("icon").toString());
  c->setId(category_id);
  c->setSequence(sequence);

  return c;
}

//------------------------------------------------------------------------------

Product *Database::product(int id) {
  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[Products]._select.arg(_prefix, "*", "id").arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }

  bool ok;
  int productId = q.value("id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("id").toString());
    return 0;
  }

  int categoryId = q.value("category_id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("category_id").toString());
    return 0;
  }

  int price = q.value("price").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("price").toString());
    return 0;
  }

  int sequence = q.value("sequence").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("sequence").toString());
    return 0;
  }

  Product *p = new Product();

  p->setName(q.value("name").toString());
  p->setIcon(q.value("icon").toString());
  p->setInfo(q.value("info").toString());
  p->setAmount(q.value("amount").toString());
  p->setCategoryId(categoryId);
  p->setId(productId);
  p->setPrice(price);
  p->setSequence(sequence);

  return p;
}

//------------------------------------------------------------------------------

Order *Database::order(int id) {
  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[Orders]._select.arg(_prefix, "*", "id").arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }

  bool ok;
  int orderId = q.value("id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("id").toString());
    return 0;
  }

  int clientId = q.value("client_id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("client_id").toString());
    return 0;
  }

  int state = q.value("state").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("state").toString());
    return 0;
  }

  // TODO: implement
  QDateTime orderSent = q.value("date_added").toDateTime();

  Order *o = new Order();

  o->setId(orderId);
  o->setClientId(clientId);
  o->setState(state);

  QList<int> itemsId;

  // if something go wrong return 0
  if (!orderItemIds(itemsId, orderId))
    return 0;

  // add order item base on id
  foreach (int orderItemId, itemsId) { o->addItem(orderItem(orderItemId)); }

  return o;
}

//------------------------------------------------------------------------------

Order *Database::order(int id, Waiter *waiter)
{
  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[Orders]._select.arg(_prefix, "*", "id").arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }

  bool ok;
  int orderId = q.value("id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("id").toString());
    return 0;
  }

  int clientId = q.value("client_id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("client_id").toString());
    return 0;
  }

  int state = q.value("state").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("state").toString());
    return 0;
  }

  int waiterState = q.value("waiter_state").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("waiter_state").toString());
    return 0;
  }

  // TODO: implement
  QDateTime orderSent = q.value("date_added").toDateTime();

  Order *o = new Order();

  o->setId(orderId);
  o->setClientId(clientId);
  o->setState(state);
  o->setWaiterState(waiterState);
  o->setTimeSent(orderSent);

  QList<int> itemsId;

  // if something go wrong return 0
  if (!orderItemIds(itemsId, orderId, waiter))
    return 0;

  // add order item base on id
  foreach (int orderItemId, itemsId) { o->addItem(orderItem(orderItemId)); }

  return o;
}

//------------------------------------------------------------------------------

Income *Database::income(int id) {
  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[Incomes]._select.arg(_prefix, "*", "id").arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }

  bool ok;
  int incomeId = q.value("id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("id").toString());
    return 0;
  }
  int day = q.value("day").toInt();
  int month = q.value("month").toInt();
  int year = q.value("year").toInt();
  QDate date;
  date.setDate(year, month, day);
  float income = q.value("income").toFloat();

  Income *i = new Income();

  i->setId(incomeId);
  i->setDate(date);
  i->setIncome(income);

  return i;
}

//------------------------------------------------------------------------------

Config *Database::config(int id) {
  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[Configs]._select.arg(_prefix, "*", "id").arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }

  bool ok;
  int configId = q.value("id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("id").toString());
    return 0;
  }

  int name = q.value("name").toInt();
  QString value = q.value("value").toString();

  Config *c = new Config();

  c->setId(configId);
  c->setName(name);
  c->setValue(value);

  return c;
}

//------------------------------------------------------------------------------

OrderItem *Database::orderItem(int id) {
  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[OrderItems]._select.arg(_prefix, "*", "id", ":id");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  q.bindValue(":id", id);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }

  bool ok;

  int productId = q.value("product_id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("product_id").toString());
    return 0;
  }

  int amount = q.value("amount").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("amount").toString());
    return 0;
  }

  double price = q.value("price").toDouble(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to double!")
                       .arg(q.value("price").toString());
    return 0;
  }

  int state = q.value("status").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("status").toString());
    return 0;
  }

  int msec = q.value("time").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("time").toString());
    return 0;
  }

  QTime time(0, 0, 0);
  time = time.addMSecs(msec);

  OrderItem *oi = new OrderItem();

  oi->setProductId(productId);
  oi->setId(id);
  oi->setAmount(amount);
  oi->setPrice(price);
  oi->setState(state);
  oi->setTime(time);

  return oi;
}

//------------------------------------------------------------------------------

Client *Database::client(int id) {
  Client *client = nullptr;

  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[Clients]._select.arg(_prefix, "*", "id", ":id");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  q.bindValue(":id", id);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }

  bool ok;

  int clientId = q.value("id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("id").toString());
    return 0;
  }

  int type = q.value("type").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("type").toString());
    return 0;
  }

  // Base on type create property account type

  switch (type) {
  case ComPackage::TableAccount: {
    client = new Table();
    client->setId(clientId);
    client->setName(q.value("name").toString());
    getTableAdditionalData(reinterpret_cast<Table *>(client));
  } break;
  case ComPackage::WaiterAccount: {
    client = new Waiter();
    client->setId(clientId);
    client->setName(q.value("name").toString());
    getWaiterAdditionalData(reinterpret_cast<Waiter *>(client));
  } break;
  case ComPackage::AdminAccount: {
    client = new Admin();
    client->setId(clientId);
    client->setName(q.value("name").toString());
  } break;
  default:
    qCritical() << tr("Account type don't exists");
    return nullptr;
  }

  return client;
}

//------------------------------------------------------------------------------

File *Database::media(int id) {

  File *fc = nullptr;

  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[Medias]._select.arg(_prefix, "*", "id" , ":id", ";");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  q.bindValue(":id", id);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }

  bool ok;

  int type = q.value("type").toInt(&ok);

  switch (type) {
  case ComPackage::AdvertisingVideo: {
    fc = new AdvertisingVideo();
    fc->_fileInfo._id=id;
    fc->_fileInfo._type=type;
    fc->_fileInfo._name=q.value("name").toString();
    fc->_fileInfo._date=q.value("date_added").toString();
    fc->_fileInfo._size=q.value("size").toInt(&ok);
    fc->_fileInfo._removed=q.value("removed").toInt(&ok);
    getAdvertisingAdditionalData(reinterpret_cast<AdvertisingVideo *>(fc));
  } break;
  case ComPackage::AdvertisingPicture: {
  } break;
  case ComPackage::CatergoryIcon: {
  } break;
  case ComPackage::ProductPicture: {
  } break;
  case ComPackage::ProductVideo: {
  } break;
  default:
    qCritical() << tr("Account type don't exists");
    return nullptr;
  }
  return fc;
}


//------------------------------------------------------------------------------

rotable::SystemUpdate *Database::systemUpdate(int id) {
    rotable::SystemUpdate *sy = new rotable::SystemUpdate;

    if (!isConnected()) {
      return 0;
    }

    QString queryStr =
        _sqlCommands[SystemUpdate]._select.arg(_prefix, "*", "id", ":id");

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return 0;
    }

    q.bindValue(":id", id);

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return 0;
    }

    if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
      if (q.size() != 1) {
        qCritical()
            << tr("Query: returned %1 results but we expected it to return 1!")
                   .arg(q.size());
        return 0;
      }
    }

    if (!q.next()) {
      return 0;
    }

    bool ok;

    sy->setId( q.value("id").toInt(&ok));
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to integer!")
                         .arg(q.value("id").toString());
      return 0;
    }

    sy->setCurrentVersion(q.value("current_version").toDouble(&ok));
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to double!")
                         .arg(q.value("id").toString());
      return 0;
    }

    sy->setAvailableVersion(q.value("available_version").toDouble(&ok));
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to double!")
                         .arg(q.value("id").toString());
      return 0;
    }

    sy->setDateCurrentVersion( q.value("date_current_version").toString());

    sy->setDateAvailableVersion( q.value("date_available_version").toString());

    return sy;

}

//------------------------------------------------------------------------------

int Database::advertisingConfig(int id) {
    int ac;

    if (!isConnected()) {
      return 0;
    }

    QString queryStr =
        _sqlCommands[AdvertisingConfig]._select.arg(_prefix, "*", "id", ":id");

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return 0;
    }

    q.bindValue(":id", id);

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return 0;
    }

    if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
      if (q.size() != 1) {
        qCritical()
            << tr("Query: returned %1 results but we expected it to return 1!")
                   .arg(q.size());
        return 0;
      }
    }

    if (!q.next()) {
      return 0;
    }

    bool ok;

    ac= q.value("frequency").toInt(&ok);
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to integer!")
                         .arg(q.value("id").toString());
      return 0;
    }

    return ac;

}

//------------------------------------------------------------------------------


bool Database::advertisingVideo(AdvertisingVideo & video) {
  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[AdvertisingVideos]._select.arg(_prefix, "*", "media_id").arg(video._fileInfo._id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }
  bool ok;

  video._advertisingInfo._playTime=q.value("playtime").toInt(&ok);
  video._advertisingInfo._id=q.value("id").toInt(&ok);
  video._advertisingInfo._play=q.value("play").toBool();
  video._advertisingInfo._played=q.value("played").toInt(&ok);
  video._advertisingInfo._duration=q.value("duration").toInt(&ok);
  return true;
}

//------------------------------------------------------------------------------

bool Database::addCategory(ProductCategory *category) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Categories]._insert.arg(
      _prefix, "NULL", ":name", ":icon", ":sequence");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", category->name());
  q.bindValue(":icon", category->icon());
  q.bindValue(":sequence", category->sequence());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::addProduct(Product *product) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Products]._insert.arg(
      _prefix, "NULL", ":name", ":price", ":info", ":category_id", ":icon",
      ":amount", ":sequence");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", product->name());
  q.bindValue(":price", product->price());
  q.bindValue(":info", product->info());
  q.bindValue(":category_id", product->categoryId());
  q.bindValue(":icon", product->icon());
  q.bindValue(":amount", product->amount());
  q.bindValue(":sequence", product->sequence());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::addUser(User *user) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Clients]._insert.arg(_prefix, "NULL", ":name", ":type");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", user->name());
  q.bindValue(":type", user->accountType());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  qint32 id = q.lastInsertId().toInt();

  queryStr = _sqlCommands[Passwords]._insert.arg(_prefix, ":id", ":password");
  q.clear();
  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":id", id);
  q.bindValue(":password", user->hashPassword());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::addIncome(Income *income) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Incomes]._insert.arg(
      _prefix, "NULL", ":income", ":day", ":month", ":year");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":income", income->income());
  q.bindValue(":day", income->date().day());
  q.bindValue(":month", income->date().month());
  q.bindValue(":year", income->date().year());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::addConfig(Config *config) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Configs]._insert.arg(_prefix, "NULL", ":name", ":value");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", config->name());
  q.bindValue(":value", config->value());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  // emit signal to parse config
  parseConfig(config);

  return true;
}

//------------------------------------------------------------------------------

bool Database::addOrder(Order *order) {
  if (!isConnected()) {
    return false;
  }

  //    qDebug() << "Begin tras:" << _db.transaction();

  QString queryStr = _sqlCommands[Orders]._insert.arg(
      _prefix, "NULL", ":state", ":income_id", ":client_id");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    _db.rollback();
    return false;
  }

  q.bindValue(":state", order->state());
  q.bindValue(":waiter_state", order->waiterState());
  q.bindValue(":income_id", getLastIncomeId());
  q.bindValue(":client_id", order->clientId());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    _db.rollback();
    return false;
  }

  int id = q.lastInsertId().toInt();

  for (int i = 0; i < order->itemCount(); ++i)
    if (!addOrderItem(order->item(i), id)) {
      _db.rollback();
      return false;
    }

  _db.commit();
  return true;
}

//------------------------------------------------------------------------------

bool Database::addOrderItem(OrderItem *item, int orderId) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[OrderItems]._insert.arg(
      _prefix, "NULL", ":order_id", ":product_id", ":amount", ":status",
      ":price", ":time");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":order_id", orderId);
  q.bindValue(":product_id", item->productId());
  q.bindValue(":amount", item->amount());
  q.bindValue(":status", item->state());
  q.bindValue(":price", item->price());
  q.bindValue(":time", item->time().msec());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::addMedia(File* file)
{
    if (!isConnected()) {
      return false;
    }
    for (auto fileInfo: file->l_fileInfo) {
        QString queryStr = _sqlCommands[Medias]._insert.arg(
            _prefix, "NULL", ":type", ":name", ":size");

        QSqlQuery q(_db);
        q.setForwardOnly(true);

        if (!q.prepare(queryStr)) {
          qCritical() << tr("Invalid query: %1").arg(queryStr);
          return false;
        }
        q.bindValue(":type", file->getType());
        q.bindValue(":name", fileInfo._name);
        q.bindValue(":size", fileInfo._size);

        if (!q.exec()) {
          qCritical()
              << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
          return false;
        }
    }
    return true;
}

//------------------------------------------------------------------------------

bool Database::addAdvertisingVideo(QList<int>* mediaId)
{

    if (!isConnected()) {
      return false;
    }
    for (int media_id: *mediaId) {
        QString queryStr = _sqlCommands[AdvertisingVideos]._insert.arg(
            _prefix, "NULL", ":playtime", ":play", ":played", ":media_id", ":duration");

        QSqlQuery q(_db);
        q.setForwardOnly(true);

        if (!q.prepare(queryStr)) {
          qCritical() << tr("Invalid query: %1").arg(queryStr);
          return false;
        }
        q.bindValue(":playtime",0);
        q.bindValue(":play",1 );
        q.bindValue(":played",0);
        q.bindValue(":media_id",media_id );
        q.bindValue(":duration",0);

        if (!q.exec()) {
          qCritical()
              << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
          return false;
        }
    }
    return true;
}

bool Database::addNewSystemUpdate(float availableSystemVersion)
{
    if (!isConnected()) {
      return false;
    }
    QString queryStr = _sqlCommands[SystemUpdate]._insert.arg(
        _prefix, "NULL", ":current_version", ":date_current_version", ":available_version", "date_available_version");

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return false;
    }
    //q.bindValue(":current_version", file->getType());
    //q.bindValue(":date_current_version", fileInfo._name);
    q.bindValue(":available_version", availableSystemVersion);

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return false;
        }
    return true;
}

//------------------------------------------------------------------------------

bool Database::addAdvertisingConfig(int frequency)
{
    if (!isConnected()) {
      return false;
    }
    QString queryStr = _sqlCommands[AdvertisingConfig]._insert.arg(
        _prefix, "NULL", ":frequency");

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return false;
    }

    q.bindValue(":frequency", frequency);

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return false;
        }
    return true;
}

//------------------------------------------------------------------------------

bool Database::updateCategory(ProductCategory *category) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Categories]._update.arg(_prefix).arg(category->id());

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", category->name());
  q.bindValue(":icon", category->icon());
  q.bindValue(":sequence", category->sequence());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::updateProduct(Product *product) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Products]._update.arg(_prefix).arg(product->id());

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", product->name());
  q.bindValue(":price", product->price());
  q.bindValue(":info", product->info());
  q.bindValue(":category_id", product->categoryId());
  q.bindValue(":icon", product->icon());
  q.bindValue(":amount", product->amount());
  q.bindValue(":sequence", product->sequence());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::updateIncome(Income *income) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Incomes]._update.arg(_prefix).arg(income->id());

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":income", income->income());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::updateConfig(Config *config) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Configs]._update.arg(_prefix).arg(config->id());

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", config->name());
  q.bindValue(":value", config->value());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  // emit signal to parse config
  parseConfig(config);

  return true;
}

//------------------------------------------------------------------------------

bool Database::updateOrder(Order *order) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Orders]._update.arg(_prefix).arg(order->id());

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":state", order->state());
  q.bindValue(":waiter_state", order->waiterState());
  q.bindValue(":client_id", order->clientId());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  for (int i = 0; i < order->itemCount(); ++i) {
    if (!updateOrderItem(order->item(i)))
      return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::updateClient(Client *client) {
  if (!isConnected() || client->id() == -1) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Clients]._update.arg(_prefix).arg(client->id());

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", client->name());
  q.bindValue(":type", client->accountType());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  switch (client->accountType()) {
  case ComPackage::WaiterAccount: {
//    Waiter *tmp = reinterpret_cast<Waiter *>(client);
  } break;
  case ComPackage::TableAccount: {
    Table *tmp = reinterpret_cast<Table *>(client);
    if (!updateTableAdditionalData(tmp->id(), tmp->isConnected(),
                                   tmp->waiterIsNeeded()))
      return false;
  } break;
  case ComPackage::AdminAccount:
    break; // throw new NotImplementedException();
  default:
    qCritical() << tr("Account type don't exist");
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::updateUserPassword(User *user)
{
  if (!isConnected() && user->id() != -1 ) {
    return false;
  }

  QString queryStr = _sqlCommands[Passwords]._update.arg(_prefix).arg(user->id());

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":password", user->hashPassword());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::updateFile(File *file) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Medias]._update.arg(_prefix).arg(file->_fileInfo._id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", file->_fileInfo._name);
  q.bindValue(":size", file->_fileInfo._size);
  q.bindValue(":removed", file->_fileInfo._removed);
  q.bindValue(":type", file->_fileInfo._type);


  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  switch (file->_fileInfo._type) {
  case ComPackage::AdvertisingVideo: {
    AdvertisingVideo *advertisingVideo = reinterpret_cast<AdvertisingVideo *>(file);
    if (!updateAdvertsingAdditionalData(advertisingVideo))
      return true;
  } break;
  return false;
  }
  return true;
}

//------------------------------------------------------------------------------

bool Database::updateTableAdditionalData(int id, int connected, int need) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[TableDetails]._update.arg(_prefix).arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":waiterIsNeeded", need);
  q.bindValue(":connected", connected);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::updateWaiterAdditionalData(Waiter *waiter) {
  Waiter *oldWaiter = reinterpret_cast<Waiter *>(client(waiter->id()));

  QList<int> *oldCategories = oldWaiter->categories(),
             *newCategories = waiter->categories();

  QList<int> toAdd, toRemove;

  for(auto var: *newCategories)
    if (!oldCategories->contains(var))
      toAdd.append(var);

  for(auto var: *oldCategories)
    if (!newCategories->contains(var))
      toRemove.append(var);

  delete oldWaiter; // Clear object, not needed. Also oldoCategries are clear
  return true;
}

//------------------------------------------------------------------------------

bool Database::updateAdvertsingAdditionalData(AdvertisingVideo *advertisingVideo) {
    if (!isConnected()) {
      return false;
    }

    QString queryStr = _sqlCommands[AdvertisingVideos]._update.arg(_prefix).arg(advertisingVideo->getA_id());

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return false;
    }

    q.bindValue(":playtime", advertisingVideo->getPlayTime());
    q.bindValue(":play", advertisingVideo->getPlay());
    q.bindValue(":played", advertisingVideo->getPlayed());
    q.bindValue(":media_id", advertisingVideo->getMedia_id());
    q.bindValue(":duration", advertisingVideo->getDuration());

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return false;
    }

    return true;
}
//------------------------------------------------------------------------------

bool Database::addWaiterCategoires(const int &waiterId,
                                   QList<int> *categoryList) {

  if (!isConnected()) {
      qCritical() << "test1";
    return false;
  }
  foreach(auto var , *categoryList){
    QString queryStr = _sqlCommands[DatabaseTables::WaiterCategories]._insert.arg(
        _prefix, ":waiter_id", ":category_id");
    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return false;
    }

    q.bindValue(":waiter_id", waiterId);
    q.bindValue(":category_id", var);

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return false;
    }

    if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
      if (q.size() != 1) {
        qCritical()
            << tr("Query: returned %1 results but we expected it to return 1!")
                   .arg(q.size());
        return 0;
      }
    }

  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::removeWaiterCategoires(const int &waiterId,
                                      QList<int> *categoryList) {
  if (!isConnected()) {
    return false;
  }
  foreach(auto var , *categoryList){
    QString queryStr = _sqlCommands[DatabaseTables::WaiterCategories]._remove.arg(
                _prefix, ":waiter_id", ":category_id");

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return false;
    }

    q.bindValue(":waiter_id", waiterId);
    q.bindValue(":category_id", var);

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return false;
    }

    if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
      if (q.size() != 1) {
        qCritical()
            << tr("Query: returned %1 results but we expected it to return 1!")
                   .arg(q.size());
        return 0;
      }
    }

  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::removeCategory(int id) {
  if (!isConnected() || id == -1) {
    return false;
  }

  //----------------------------------------------------------------------------
  // Remove products:
  {
    QString queryStr = QString(S_deleteProductsOfCategory).arg(_prefix).arg(id);

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return false;
    }

    if (!q.exec()) {
      qCritical() << tr("Query exec failed: (%1: %2")
                         .arg(queryStr, q.lastError().text());
      return false;
    }
  }

  //----------------------------------------------------------------------------
  // Remove category:
  {
    QString queryStr = _sqlCommands[Categories]._remove.arg(_prefix).arg(id);

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return false;
    }

    if (!q.exec()) {
      qCritical() << tr("Query exec failed: (%1: %2")
                         .arg(queryStr, q.lastError().text());
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::removeProduct(int id) {
  if (!isConnected() || id == -1) {
    return false;
  }

  QString queryStr = _sqlCommands[Products]._remove.arg(_prefix).arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::removeIncome(int id) {
  if (!isConnected() || id == -1) {
    return false;
  }

  QString queryStr = _sqlCommands[Incomes]._remove.arg(_prefix).arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::removeConfig(int id) {
  if (!isConnected() || id == -1) {
    return false;
  }

  QString queryStr = _sqlCommands[Configs]._remove.arg(_prefix).arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------
bool Database::removeFile(int id, int remove)
{
    if (!isConnected()) {
      return false;
    }

    QString queryStr = _sqlCommands[Medias]._remove.arg(_prefix).arg(id).arg(remove);

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return -1;
    }

    q.bindValue(":id", id);
    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return false;
    }

    return true;
}

//------------------------------------------------------------------------------

bool Database::createDatabase() {
  if (!isConnected()) {
    return false;
  }

  if (_db.transaction())
    qCritical() << tr("Create new transaction");
  // Set time zone is not available when using SQLITE
  // ret &= dbExec(QString("SET time_zone =
  // \"%1\";").arg(ROTABLE_DATABASE_TIMEZONE));

  // Category table
  QSqlQuery q1(QString("DROP TABLE IF EXISTS `%1categories`;").arg(_prefix),
               _db);
  if (q1.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q1.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q2(_sqlCommands[Categories]._create.arg(_prefix), _db);
  if (q2.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q2.lastError().text());
    _db.rollback();
    return false;
  }

  // Product table
  QSqlQuery q3(QString("DROP TABLE IF EXISTS `%1products`;").arg(_prefix), _db);
  if (q3.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q3.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q4(_sqlCommands[Products]._create.arg(_prefix), _db);
  if (q4.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q4.lastError().text());
    return false;
  }

  //  That table don't exists (don't exist in sql commands, don't create in
  //  other way)
  //  QSqlQuery q5(QString("DROP TABLE IF EXISTS `%1tables`;").arg(_prefix),
  //  _db);
  //  if (q5.lastError().type() != QSqlError::NoError) {
  //    qCritical() << tr("Query exec failed: %1").arg(q5.lastError().text());
  //    return false;
  //  }

  // Client table
  QSqlQuery q5(QString("DROP TABLE IF EXISTS `%1clients`;").arg(_prefix), _db);
  if (q5.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q5.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q6(_sqlCommands[Clients]._create.arg(_prefix), _db);
  if (q6.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q6.lastError().text());
    _db.rollback();
    return false;
  }

  // Order table
  QSqlQuery q9(QString("DROP TABLE IF EXISTS `%1order`;").arg(_prefix), _db);
  if (q9.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q9.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q10(_sqlCommands[Orders]._create.arg(_prefix), _db);
  if (q10.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q10.lastError().text());
    _db.rollback();
    return false;
  }
  // Order_item table
  QSqlQuery q11(QString("DROP TABLE IF EXISTS `%1order_items`;").arg(_prefix),
                _db);
  if (q11.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q11.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q12(_sqlCommands[OrderItems]._create.arg(_prefix), _db);
  if (q12.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q12.lastError().text());
    _db.rollback();
    return false;
  }

  // Incomes table
  QSqlQuery q13(QString("DROP TABLE IF EXISTS `%1daily_incomes`;").arg(_prefix),
                _db);
  if (q13.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q13.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q14(_sqlCommands[Incomes]._create.arg(_prefix), _db);
  if (q14.lastError().type() != QSqlError::NoError) {
    _db.rollback();
    qCritical() << tr("Query exec failed: %1").arg(q14.lastError().text());
    return false;
  }

  // Configs table
  QSqlQuery q15(QString("DROP TABLE IF EXISTS `%1configs`;").arg(_prefix), _db);
  if (q15.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q15.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q16(_sqlCommands[Configs]._create.arg(_prefix), _db);
  if (q16.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q16.lastError().text());
    _db.rollback();
    return false;
  }

  // Configs table
  QSqlQuery q17(QString("DROP TABLE IF EXISTS `%1mac_adresses`;").arg(_prefix),
                _db);
  if (q17.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q17.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q18(_sqlCommands[MacAdresses]._create.arg(_prefix), _db);
  if (q18.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q18.lastError().text());
    _db.rollback();
    return false;
  }

  // Configs table
  QSqlQuery q19(QString("DROP TABLE IF EXISTS `%1passwords`;").arg(_prefix),
                _db);
  if (q19.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q19.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q20(_sqlCommands[Passwords]._create.arg(_prefix), _db);
  if (q20.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q20.lastError().text());
    _db.rollback();
    return false;
  }

  // Configs table
  QSqlQuery q21(QString("DROP TABLE IF EXISTS `%1table_details`;").arg(_prefix),
                _db);
  if (q21.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q21.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q22(_sqlCommands[TableDetails]._create.arg(_prefix), _db);
  if (q22.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q22.lastError().text());
    _db.rollback();
    return false;
  }

  // WaiterConfig table
  QSqlQuery q23(QString("DROP TABLE IF EXISTS `%1waitercategories`;").arg(_prefix),
                _db);
  if (q23.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q23.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q24(_sqlCommands[WaiterCategories]._create.arg(_prefix), _db);
  if (q24.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q24.lastError().text());
    _db.rollback();
    return false;
  }

  // Media table
  QSqlQuery q25(QString("DROP TABLE IF EXISTS `%1medias`;").arg(_prefix),
                _db);
  if (q25.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q25.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q26(_sqlCommands[Medias]._create.arg(_prefix), _db);
  if (q26.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q26.lastError().text());
    _db.rollback();
    return false;
  }

  //AdvertisingVideos table
  QSqlQuery q27(QString("DROP TABLE IF EXISTS `%1advertisingvideos`;").arg(_prefix),
                _db);
  if (q27.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q27.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q28(_sqlCommands[AdvertisingVideos]._create.arg(_prefix), _db);
  if (q28.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q28.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q29(_sqlCommands[SystemUpdate]._create.arg(_prefix), _db);
  if (q29.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q29.lastError().text());
    _db.rollback();
    return false;
  }

  QSqlQuery q30(_sqlCommands[AdvertisingConfig]._create.arg(_prefix), _db);
  if (q30.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q30.lastError().text());
    _db.rollback();
    return false;
  }

  if (!initTriggers()) {
    _db.rollback();
    return false;
  }
  if (!add_init_data()) {
    _db.rollback();
    return false;
  }

  _db.commit();

  return true;
}

//------------------------------------------------------------------------------

bool Database::exportDatabase(const QString &path, bool binary) {
  if (!isConnected()) {
    return false;
  }

  QString command;
  if (!exportDatabase(command)) {
    return false;
  }

  if (binary) {
    qDebug() << tr("Binary database exports are currently not implemented!");
    return false;
  } else {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() << tr("Could not open file \"%1\" to write").arg(path);
      return false;
    }

    QTextStream out(&file);
    out << command;

    file.close();
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::exportDatabase(QString &dest) {
  if (!isConnected()) {
    return false;
  }

  // Add drop table commands
  dest += QString("DROP TABLE IF EXISTS `%1categories`;\n").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1products`;\n").arg(_prefix);
  // TODO: chceck is it need'ed
  // dest += QString("DROP TABLE IF EXISTS `%1tables`;").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1clients`;").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1order`;").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1order_item`;").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1daily_incomes`;").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1configs`;").arg(_prefix);
  dest += QString("DROP TRIGGER IF EXISTS `%1update_orderitem_status_add`;")
              .arg(_prefix);
  dest += QString("DROP TRIGGER IF EXISTS `%1update_orderitem_status_remove`;")
              .arg(_prefix);

  // Add create table command
  dest += _sqlCommands[Categories]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[Products]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[Clients]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[Orders]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[OrderItems]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[Incomes]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[Configs]._create.arg(_prefix) + '\n';

  // Add triggers
  dest +=
      QString((const char *)QResource(
                  QString("://sql-commands/trigger_update_orderitem_add.sql"))
                  .data());
  dest += QString(
      (const char *)QResource(
          QString("://sql-commands/trigger_update_orderitem_remove.sql"))
          .data());

  //-------------------------------------------------------------------------------
  // Add insert command with data
  //-------------------------------------------------------------------------------
  // Category
  QList<int> ids;
  if (categoryIds(ids)) {
    for (int i = 0; i < ids.size(); ++i) {
      ProductCategory *c = category(ids[i]);
      if (c) {
        dest += _sqlCommands[Categories]
                    ._insert.arg(_prefix)
                    .arg(c->id())
                    .arg('\'' + c->name() + '\'')
                    .arg('\'' + c->icon() + '\'');
        dest += '\n';
        delete c;
      } else {
        return false;
      }
    }
  } else {
    return false;
  }
  // Product
  ids.clear();
  if (productIds(ids, -1)) {
    for (int i = 0; i < ids.size(); ++i) {
      Product *p = product(ids[i]);
      if (p) {
        dest += _sqlCommands[Products]
                    ._insert.arg(_prefix)
                    .arg(p->id())
                    .arg('\'' + p->name() + '\'')
                    .arg(p->price())
                    .arg('\'' + p->info() + '\'')
                    .arg(p->categoryId())
                    .arg('\'' + p->icon() + '\'')
                    .arg('\'' + p->amount() + '\'');
        dest += '\n';
        delete p;
      } else {
        return false;
      }
    }
  } else {
    return false;
  }
  // TODO: export Waiter table
  // TODO: export Client table
  // TODO: export Order table
  // TODO: export OrderList table
  // TODO: export Incomes table
  // TODO: export Configs table
  // TODO: export Passwords table
  // TODO: export MacAdresses table
  // TODO: export TableDetails tables
  throw new NotImplementedException();
  return true;
}

//------------------------------------------------------------------------------

bool Database::databaseExists() const {
  if (!isConnected()) {
    return false;
  }

  QStringList tables = _db.tables(QSql::Tables);

  foreach (QString t, tables) { qDebug() << t; }

  if (tables.contains(QString("%1categories").arg(_prefix)) &&
      tables.contains(QString("%1products").arg(_prefix))) {
    return true;
  } else {
    return false;
  }
}

//------------------------------------------------------------------------------

bool Database::hasCategory(const QString &name) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Categories]._select.arg(
      _prefix, "`id`", "name", QString("'%1'").arg(name));

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return q.next();
}

//------------------------------------------------------------------------------

bool Database::hasCategory(int id) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Categories]._select.arg(
      _prefix, "`id`", "id", QString("'%1'").arg(id));

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return q.next();
}

//------------------------------------------------------------------------------

bool Database::hasProduct(const QString &name, int categoryId) {
  if (!isConnected() || name.isEmpty() || categoryId == -1) {
    return false;
  }

  QString queryStr = _sqlCommands[Products]._select.arg(
      _prefix, "`id`", "name", QString("'%1'").arg(name));
  queryStr += QString(" AND `category_id` = %1").arg(categoryId);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return q.next();
}

//------------------------------------------------------------------------------

bool Database::hasProduct(int productId, int categoryId) {
  if (!isConnected() || productId == -1 || categoryId == -1) {
    return false;
  }

  QString queryStr = _sqlCommands[Products]._select.arg(
      _prefix, "`name`", "id", QString("'%1'").arg(productId));
  queryStr += QString(" AND `category_id` = %1").arg(categoryId);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return q.next();
}

//------------------------------------------------------------------------------

int Database::hasUser(const QString &nick, const QString &passwdHash) {
  // Check if we have connection with database and nick and password
  // are set
  if (!isConnected() || nick.isEmpty() || passwdHash.isEmpty()) {
    return false;
  }

  //    QString queryStr = _sqlCommands[Clients]._select
  //                       .arg(_prefix, "`id`", "name", ":name");

  QString queryStr = _sqlCommands[Clients]._select.arg(
      _prefix, "`id`", "name", QString("\"" + nick + "\""));

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  // Should work but don't work :'(
  // q.bindValue(":nick", nick);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return -1;
  }
  // qDebug << tr("Last query: ") << q.lastQuery();
  // qCritical()  << tr("Last query: ") << q.lastQuery();
  if (!q.next()) {
    return 0;
  }

  bool ok;
  int id = q.value("id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("id").toString());
    return 0;
  }

  queryStr = _sqlCommands[Passwords]._select.arg(
      _prefix, "`id`", "id", ":id AND password = :password");

  //    Waiter user;
  //    user.setPassword(passwdHash);

  //    queryStr = _sqlCommands[Passwords]._select
  //            .arg(_prefix, "`id`", "id", QString(QString::number(id) +" AND
  //            password = \"" +
  //                                               user.hashPassword() +"\""));

  q.clear();
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  q.bindValue(":id", id);
  q.bindValue(":password", Waiter::generateHashPassword(passwdHash));
  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return -1;
  }

  if (q.next()) {
    return q.value("id").toInt(&ok);
  }

  return -1;
}

//------------------------------------------------------------------------------

int Database::hasIncome(QDate date) {
  if (!isConnected() || !date.isValid()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Incomes]._select.arg(_prefix, "`id`", "day", ":day");
  queryStr += QString(" AND `month` = :month AND `year` = :year");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  q.bindValue(":day", date.day());
  q.bindValue(":month", date.month());
  q.bindValue(":year", date.year());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return -1;
  }

  if (q.next()) {
    QSqlRecord rec = q.record();

    return rec.value(rec.indexOf("id")).toInt();
  }

  return -1;
}

//------------------------------------------------------------------------------

QList<int> *Database::hasIncome(int mounth, int year) {
  if (!isConnected() || mounth < 1 || mounth > 12 || year < 2015) {
    return NULL;
  }

  QString queryStr =
      _sqlCommands[Incomes]._select.arg(_prefix, "`id`", "1", "1");
  queryStr += QString(" AND `day` >= :day1");
  queryStr += QString(" AND `day` <= :day2");
  queryStr += QString(" AND `month` >= :month1");
  queryStr += QString(" AND `month` <= :month2");
  queryStr += QString(" AND `year` >= :year1");
  queryStr += QString(" AND `year` <= :year2;");
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return NULL;
  }
  // If we want search income from january 2015 then we take
  // all income afer (with 1-st) 1 january and before 1 february
  QDate date1(1, mounth, year), date2(1, mounth + 1, year);

  q.bindValue(":day1", date1.day());
  q.bindValue(":month1", date1.month());
  q.bindValue(":year1", date1.year());
  q.bindValue(":day2", date2.day());
  q.bindValue(":month2", date2.month());
  q.bindValue(":year2", date2.year());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return NULL;
  }

  QList<int> *list = new QList<int>();

  if (q.next()) {
    QSqlRecord rec = q.record();

    list->append(rec.value(rec.indexOf("id")).toInt());
  }

  if (list->isEmpty())
    return NULL;
  else
    return list;
}

//------------------------------------------------------------------------------

int Database::hasIncome(int id) {
  if (!isConnected() || id <= 0) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Incomes]._select.arg(_prefix, "`id`", "id", ":id");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  q.bindValue(":id", id);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return -1;
  }

  if (q.next()) {
    QSqlRecord rec = q.record();

    return rec.value(rec.indexOf("id")).toInt();
  }

  return -1;
}

//------------------------------------------------------------------------------

int Database::hasConfigName(int name) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Configs]._select.arg(_prefix, "`id`", "`name`", ":name");
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  q.bindValue(":name", name);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return -1;
  }

  if (q.next()) {
    QSqlRecord rec = q.record();

    return rec.value(rec.indexOf("id")).toInt();
  }

  return -1;
}

//------------------------------------------------------------------------------

bool Database::hasConfig(int id) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Configs]._select.arg(_prefix, "`id`", "`id`", ":id");
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  q.bindValue(":id", id);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return -1;
  }
  if(q.last())
      return true;
  if (q.next()) {
    return true;
  }

  return -1;
}

//------------------------------------------------------------------------------

int Database::hasMacAddress(QString macAdresses) {
  QString queryStr = _sqlCommands[MacAdresses]._select.arg(
      _prefix, "`id`", "mac_address", ":mac_address");
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  q.bindValue(":mac_address", macAdresses);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return -1;
  }
  if (!q.next()) {
    return -1;
  }

  bool ok;
  int id = q.value("id").toInt(&ok);

  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!")
                       .arg(q.value("id").toString());
    return -1;
  }

  return id;
}

//------------------------------------------------------------------------------

bool Database::hasOrder(int id) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Orders]._select.arg(_prefix, "`id`", "id", ":id");
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  q.bindValue(":id", id);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  if(q.last())
      return true;
  if (q.next()) {
    return true;
  }

  return false;
}

//------------------------------------------------------------------------------

bool Database::hasFile(int id)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[Medias]._select.arg(_prefix, "`id`", "id", ":id");
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  q.bindValue(":id", id);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  if(q.last())
      return true;
  if (q.next()) {
    return true;
  }

  return false;
}

//------------------------------------------------------------------------------

bool Database::hasAdvertising(int media_id)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr =
      _sqlCommands[AdvertisingVideos]._select.arg(_prefix, "`id`", "media_id", ":media_id");
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  q.bindValue(":media_id", media_id);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }
  if(q.last())
      return true;
  if (q.next()) {
    return true;
  }

  return false;
}

//------------------------------------------------------------------------------
bool Database::hasFile(QString name, int type)
{
    if (!isConnected()) {
      return false;
    }

    QString queryStr =
            "SELECT `id` FROM rotable_medias WHERE `name` = :name AND `type` = :type ;";
    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return -1;
    }

    q.bindValue(":name", name);
    q.bindValue(":type", type);

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return false;
    }
    /*if(q.last())
        return true;*/
    if (q.next()) {
      return true;
    }

    return false;
}


//------------------------------------------------------------------------------

QList<Order *> *Database::getNotCloseOrderList() {
  if (!isConnected()) {
    return 0;
  }

  QList<Order *> *list = new QList<Order *>();

  QString queryStr = QString("SELECT %2 FROM `%1orders` WHERE `%3` != %4;")
                         .arg(_prefix, "*", "state", ":stat");

  QSqlQuery q(_db);
  q.setForwardOnly(false);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    delete list;
    return 0;
  }

  q.bindValue(":stat", "5");

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    delete list;
    return 0;
  }

  //    if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
  //      if (q.size() != 1) {
  //        qCritical() << tr("Query: returned %1 results but we expected it to
  //        return 1!")
  //                       .arg(q.size());
  //        delete list;
  //        return 0;
  //      }
  //    }

  if (!q.next()) {
    delete list;
    return 0;
  }

  do {

    bool ok;
    int orderId = q.value("id").toInt(&ok);
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to integer!")
                         .arg(q.value("id").toString());
      delete list;
      return 0;
    }

    int clientId = q.value("client_id").toInt(&ok);
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to integer!")
                         .arg(q.value("client_id").toString());
      delete list;
      return 0;
    }

    int state = q.value("state").toInt(&ok);
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to integer!")
                         .arg(q.value("state").toString());
      delete list;
      return 0;
    }

    int waiterState = q.value("waiter_state").toInt(&ok);
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to integer!")
                         .arg(q.value("state").toString());
      delete list;
      return 0;
    }

    QDateTime orderSent = q.value("date_added").toDateTime();

    Order *o = new Order();

    o->setId(orderId);
    o->setClientId(clientId);
    o->setState(state);
    o->setWaiterState(waiterState);

    QList<int> itemsId;

    // if something go wrong return 0
    if (!orderItemIds(itemsId, orderId))
      return 0;

    // add order item base on id
    foreach (int orderItemId, itemsId) { o->addItem(orderItem(orderItemId)); }
    list->append(o);
  } while (q.next());

  return list;
}

//------------------------------------------------------------------------------

QList<Order *> *Database::getNotDoneOrderList() {
  if (!isConnected()) {
    return 0;
  }

  QList<Order *> *list = new QList<Order *>();

  QString queryStr = QString("SELECT %2 FROM `%1orders` WHERE `%3` == %4;")
                         .arg(_prefix, "*", "state", ":stat");

  QSqlQuery q(_db);
  q.setForwardOnly(false);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    delete list;
    return 0;
  }

  q.bindValue(":stat", "1");

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    delete list;
    return 0;
  }

  //    if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
  //      if (q.size() != 1) {
  //        qCritical() << tr("Query: returned %1 results but we expected it to
  //        return 1!")
  //                       .arg(q.size());
  //        delete list;
  //        return 0;
  //      }
  //    }

  if (!q.next()) {
    delete list;
    return 0;
  }

  do {

    bool ok;
    int orderId = q.value("id").toInt(&ok);
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to integer!")
                         .arg(q.value("id").toString());
      delete list;
      return 0;
    }

    int clientId = q.value("client_id").toInt(&ok);
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to integer!")
                         .arg(q.value("client_id").toString());
      delete list;
      return 0;
    }

    int state = q.value("state").toInt(&ok);
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to integer!")
                         .arg(q.value("state").toString());
      delete list;
      return 0;
    }

    QDateTime orderSent = q.value("date_added").toDateTime();

    Order *o = new Order();

    o->setId(orderId);
    o->setClientId(clientId);
    o->setState(state);

    QList<int> itemsId;

    // if something go wrong return 0
    if (!orderItemIds(itemsId, orderId))
      return 0;

    // add order item base on id
    foreach (int orderItemId, itemsId) { o->addItem(orderItem(orderItemId)); }
    list->append(o);
  } while (q.next());

  return list;
}

//------------------------------------------------------------------------------

QMap<int, QMap<int, int>> *Database::getOrderQueueList() {

  if (!isConnected()) {
    return nullptr;
  }

  QMap<int, QMap<int, int>> *result = new QMap<int, QMap<int, int>>();

  QString queryStr =
      QString("SELECT %1clients.id as `client_id`, ifnull(%1orders.id, -1) as "
              "`order_id` FROM %1clients "
              "LEFT OUTER JOIN %1orders "
              "ON %1clients.id = %1orders.client_id and %1orders.state = %3 "
              "WHERE %1clients.type = %2 ORDER BY order_id")
          .arg(_prefix, ":type", ":stat");

  QSqlQuery q(_db);
  q.setForwardOnly(false);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    delete result;
    return nullptr;
  }

  q.bindValue(":type", "1");
  q.bindValue(":stat", "1");

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    delete result;
    return nullptr;
  }

  if (!q.next()) {
    delete result;
    return nullptr;
  }

  int i = 1;
  do {
    int order_id = q.value("order_id").toInt();
    int client_id = q.value("client_id").toInt();
    if (order_id == -1)
      (*result)[client_id].clear();
    else {
      (*result)[client_id][i] = order_id;
      ++i;
    }

  } while (q.next());

  return result;
}

//------------------------------------------------------------------------------

Income *Database::getLastIncome() {
  int id = getLastIncomeId();
  return income(id);
}

//------------------------------------------------------------------------------

int Database::getLastIncomeId() {
  if (!isConnected()) {
    return -1;
  }

  QString queryStr =
      QString("SELECT MAX(id)  FROM %1daily_incomes;").arg(_prefix);
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return -1;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return -1;
  }

  if (q.next()) {
    QSqlRecord rec = q.record();

    return rec.value(rec.indexOf("MAX(id)")).toInt();
  }

  return -1;
}

//------------------------------------------------------------------------------

rotable::SystemUpdate *Database::systemUpdate() {
  rotable::SystemUpdate *sy;
    if (!isConnected()) {
    return 0;
  }

  QString queryStr = QString("SELECT MAX(id)  FROM %1systemupdate;").arg(_prefix);
  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return nullptr;
  }

  int id;

  if (q.next()) {
    QSqlRecord rec = q.record();

    id= rec.value(rec.indexOf("MAX(id)")).toInt();
  }

  sy=systemUpdate(id);

  return sy;

}

//------------------------------------------------------------------------------
QList<int> *Database::getMediaIdByType(int type, int removed)
{
    if (!isConnected()) {
      return NULL;
    }

    QString queryStr =
        _sqlCommands[Medias]._select.arg(_prefix, "`id`", "type", ":type","AND `removed` = :removed;"
);
    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return NULL;
    }

    q.bindValue(":type", type);
    q.bindValue(":removed", removed);

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return NULL;
    }

    QList<int> *list = new QList<int>();

    while (q.next()) {
      bool toIntOk=true;
      *list<<q.value("id").toInt(&toIntOk);
      if(!toIntOk){
          qCritical() << tr("Could not convert entry '%1' to an integer!")
                             .arg(q.value("id").toString());
          list->clear();
          return NULL;
      }
    }

    if (list->isEmpty())
    {
        list->append(-1);
      return list;
    }
    else
      return list;

}

//------------------------------------------------------------------------------

QList<int> *Database::getMediaIdByNameAndType(QStringList nameList, int type)
{
    if (!isConnected()) {
      return NULL;
    }

    QList<int> *list = new QList<int>();

    for(QString name: nameList){
        QString queryStr =
            "SELECT `id` FROM rotable_medias WHERE `name` = :name AND `type` = :type ;";
        QSqlQuery q(_db);
        q.setForwardOnly(true);

        if (!q.prepare(queryStr)) {
          qCritical() << tr("Invalid query: %1").arg(queryStr);
          return NULL;
        }

        q.bindValue(":name", name);
        q.bindValue(":type", type);
        if (!q.exec()) {
          qCritical()
              << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
          return NULL;
        }

        if (q.next()){
            bool toIntOk=true;
            *list<<q.value("id").toInt(&toIntOk);
            if(!toIntOk){
                qCritical() << tr("Could not convert entry '%1' to an integer!")
                                 .arg(q.value("id").toString());
                list->clear();
                return NULL;
            }
        }
    }
    if (list->isEmpty())
      return NULL;
    else
      return list;

}

//------------------------------------------------------------------------------

int Database::getLastAdvertisingConfig()
{
    if (!isConnected()) {
      return -1;
    }

    QString queryStr =
        QString("SELECT MAX(id)  FROM %1advertisingconfigs;").arg(_prefix);
    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return -1;
    }

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return -1;
    }

    if (q.next()) {
      QSqlRecord rec = q.record();

      return advertisingConfig(rec.value(rec.indexOf("MAX(id)")).toInt());
    }

    return -1;
}



//------------------------------------------------------------------------------

bool Database::isConnected() const {
  if (_connected) {
    return _db.isOpen();
  }
  return false;
}

//------------------------------------------------------------------------------

bool Database::add_init_data() {

  // ToDo: Change this to exec some sql command, or load data from json/xml,
  // etc.
  Config day;
  day.setName(Config::day_begin);
  day.setValue("16:00");

  Config closeState;
  closeState.setName(Config::closeState);
  closeState.setValue(QString("%1,%2;%3")
                          .arg(QString::number(rotable::OrderItem::New),
                               QString::number(rotable::OrderItem::ToPay),
                               QString::number(rotable::OrderItem::Pay)));

  Config dbv;
  dbv.setName(Config::dbVersion);
  dbv.setValue(newestVesion);

  Config trigger;
  trigger.setName(Config::triggerProductUpdate);
  trigger.setValue("1");

  bool ok = addConfig(&day);
  ok = ok && addConfig(&closeState);
  ok = ok && addConfig(&dbv);

  Waiter waiter;
  waiter.setName("TestWaiter");
  waiter.setPassword("TestWaiter");

  ok = ok && addUser(&waiter);

  Admin admin;
  admin.setName("debugAdmin");
  admin.setPassword("debugAdmin");
  ok = ok && addUser(&admin);

  return ok;
}

//------------------------------------------------------------------------------

int Database::registerTable(QString name, QString macAdresses) {
  if (!isConnected() || name.isEmpty() || macAdresses.isEmpty()) {
    return false;
  }

  int id = hasMacAddress(macAdresses);
  if (id == -1) {
    QString queryStr =
        _sqlCommands[Clients]._insert.arg(_prefix, "NULL", ":name", ":type");
    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return -1;
    }

    q.bindValue(":name", name);
    q.bindValue(":type", 1);

    if (!q.exec()) {
      qCritical() << tr("Query exec failed: (%1: %2")
                         .arg(queryStr, q.lastError().text());
      return -1;
    }

    id = q.lastInsertId().toInt();

    q.clear();

    queryStr =
        _sqlCommands[MacAdresses]._insert.arg(_prefix, ":id", ":mac_address");
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return -1;
    }

    q.bindValue(":id", id);
    q.bindValue(":mac_address", macAdresses);

    if (!q.exec()) {
      qCritical() << tr("Query exec failed: (%1: %2")
                         .arg(queryStr, q.lastError().text());
      return -1;
    }

    q.clear();

    queryStr = _sqlCommands[TableDetails]._insert.arg(_prefix, ":id", ":waiter",
                                                      ":connected");
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return -1;
    }

    q.bindValue(":id", id);
    q.bindValue(":waiter", false);
    q.bindValue(":connected", true);
    if (!q.exec()) {
      qCritical() << tr("Query exec failed: (%1: %2")
                         .arg(queryStr, q.lastError().text());
      return -1;
    }

    return id;
  }

  changeTableConnectStatus(id, true);

  return id;
}

//------------------------------------------------------------------------------

bool Database::changeTableConnectStatus(int idTable, bool connected) {
  return updateTableAdditionalData(idTable, connected, false);
}

//------------------------------------------------------------------------------

bool Database::setWaiterNeed(bool need, int clientId) {
  Table *tmp = reinterpret_cast<Table *>(client(clientId));
  if (!tmp)
    return false;
  tmp->setwaiterIsNeedede(need);
  return updateClient(tmp);
}

//------------------------------------------------------------------------------

QString Database::databasebVersion() {
  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[Configs]._select.arg(_prefix, "*", "name", ":name");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  q.bindValue(":name", rotable::Config::dbVersion);

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (!q.next()) {
    return "0.0.0";
  }
  return q.value("value").toString();
}

//------------------------------------------------------------------------------

void Database::updateDatabase(QString actualVersion) {
  switch (versionToEnum(actualVersion)) {
  case version0d0d0:
    updateToVersion("0.0.1");
  case version0d0d1:
    updateToVersion("0.0.2");
  case version0d0d2:
    updateToVersion("0.0.3");
  case version0d0d3:
    updateToVersion("0.0.4");
  case version0d0d4:
    updateToVersion("0.0.5");
  case version0d0d5:
    updateToVersion("0.0.6");
  case version0d0d6:
    updateToVersion("0.0.7");
  case version0d0d7:
    updateToVersion("0.0.8");
  case version0d0d8:
    updateToVersion("0.0.9");
  }
}

//------------------------------------------------------------------------------

bool Database::updateToVersion(QString version) {
  QStringList updateList =
      QString(
          (const char *)QResource(
              QString("://sql-commands/update-database/" + version + ".sql"))
              .data())
          .split(";;");
  _db.transaction();

  // SQLite can query one statment at time
  foreach (QString update, updateList) {
      LogManager::getInstance()->logInfo(update);
    QSqlQuery query(update.arg(_prefix).trimmed(), _db);
    query.executedQuery();
    if (query.lastError().type() != QSqlError::NoError) {
      qCritical() << tr("Query exec failed: %1").arg(query.lastError().text());
      _db.rollback();
      return false;
    }
  }
  _db.commit();

  return true;
}

//------------------------------------------------------------------------------

int Database::versionToEnum(QString version) {
  if (version == "0.0.1")
    return version0d0d1;
  else if (version == "0.0.2")
    return version0d0d2;
  else if (version == "0.0.3")
    return version0d0d3;
  else if (version == "0.0.4")
    return version0d0d4;
  else if (version == "0.0.5")
    return version0d0d5;
  else if (version == "0.0.6")
    return version0d0d6;
  else if (version == "0.0.7")
    return version0d0d7;
  else if (version == "0.0.8")
    return version0d0d8;
  else if (version == "0.0.9")
    return version0d0d9;
  return version0d0d0;
}

//------------------------------------------------------------------------------

void Database::update() {
  QString version = databasebVersion();
  if (version != newestVesion)
    updateDatabase(version);
}

//------------------------------------------------------------------------------

void Database::getLastIncomeDate(QDate *date) { Q_UNUSED(date); }

//------------------------------------------------------------------------------

void Database::collectSqlCommands(Database::SqlCommands &cmds, QString table) {
  cmds._create =
      QString((const char *)QResource(
                  QString("://sql-commands/%1_create.sql").arg(table))
                  .data());
  cmds._select =
      QString((const char *)QResource(
                  QString("://sql-commands/%1_select.sql").arg(table))
                  .data());
  cmds._update =
      QString((const char *)QResource(
                  QString("://sql-commands/%1_update.sql").arg(table))
                  .data());
  cmds._insert =
      QString((const char *)QResource(
                  QString("://sql-commands/%1_insert.sql").arg(table))
                  .data());
  cmds._listIds =
      QString((const char *)QResource(
                  QString("://sql-commands/%1_select_ids.sql").arg(table))
                  .data());
  cmds._remove =
      QString((const char *)QResource(
                  QString("://sql-commands/%1_remove.sql").arg(table))
                  .data());

  Q_ASSERT(!cmds._create.isEmpty());
  Q_ASSERT(!cmds._select.isEmpty());
  Q_ASSERT(!cmds._update.isEmpty());
  Q_ASSERT(!cmds._insert.isEmpty());
  Q_ASSERT(!cmds._listIds.isEmpty());
  Q_ASSERT(!cmds._remove.isEmpty());
}

//------------------------------------------------------------------------------

bool Database::getTableAdditionalData(Table *table) {
  if (!isConnected()) {
    return 0;
  }

  QString queryStr =
      _sqlCommands[TableDetails]._select.arg(_prefix, "*", "id", ":id");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  q.bindValue(":id", table->id());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

  if (!q.next()) {
    return 0;
  }

  bool waiterIsNeeded = q.value("waiterIsNeeded").toBool();
  bool connected = q.value("connected").toBool();

  table->setwaiterIsNeedede(waiterIsNeeded);
  table->setIsConnected(connected);

  return true;
}

//------------------------------------------------------------------------------

bool Database::getWaiterAdditionalData(Waiter *waiter) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[DatabaseTables::WaiterCategories]._select.arg(
      _prefix, "*", "waiter_id", ":id");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":id", waiter->id());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical()
          << tr("Query: returned %1 results but we expected it to return 1!")
                 .arg(q.size());
      return 0;
    }
  }

/*  if (!q.next()) {
    return false;
  }
*/
  QList<int> *list = new QList<int>;

  while (q.next()) {
    bool toIntOk;
    *list << q.value("category_id").toInt(&toIntOk);
    if (!toIntOk) {
      qCritical() << tr("Could not convert entry '%1' to an integer!")
                         .arg(q.value("id").toString());
      list->clear();
      return false;
    }
  }

  if (list)
    waiter->setCategories(list);

  return true;
}

bool Database::getAdvertisingAdditionalData(AdvertisingVideo* advertisingvideo)
{
    if (!isConnected()) {
      return false;
    }

    QString queryStr = _sqlCommands[AdvertisingVideos]._select.arg(
        _prefix, "*", "media_id", ":id");

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return false;
    }

    q.bindValue(":id",advertisingvideo->_fileInfo._id);

    if (!q.exec()) {
      qCritical()
          << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
      return false;
    }

    if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
      if (q.size() != 1) {
        qCritical()
            << tr("Query: returned %1 results but we expected it to return 1!")
                   .arg(q.size());
        return 0;
      }
    }

    if (!q.next()) {
      return false;
    }
    bool ok;
    advertisingvideo->_advertisingInfo._playTime=q.value("playtime").toInt(&ok);
    advertisingvideo->_advertisingInfo._id=q.value("id").toInt(&ok);
    advertisingvideo->_advertisingInfo._play=q.value("play").toBool();
    advertisingvideo->_advertisingInfo._played=q.value("played").toInt(&ok);
    advertisingvideo->_advertisingInfo._mediaId=q.value("media_id").toInt(&ok);
    advertisingvideo->_advertisingInfo._duration=q.value("duration").toInt(&ok);

    return true;
}

//------------------------------------------------------------------------------

bool Database::updateOrderItem(OrderItem *item) {
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[OrderItems]._update.arg(_prefix);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":amount", item->amount());
  q.bindValue(":price", item->price());
  q.bindValue(":state", item->state());
  q.bindValue(":time", 0);
  q.bindValue(":id", item->id());

  if (!q.exec()) {
    qCritical()
        << tr("Query exec failed: (%1: %2").arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::initTriggers() {
  if (!isConnected()) {
    return false;
  }

  // TODO: Add auto search triggers and load them
  QString trigger1 =
      QString((const char *)QResource(
                  QString("://sql-commands/trigger_update_orderitem_add.sql"))
                  .data());
  QString trigger2 = QString(
      (const char *)QResource(
          QString("://sql-commands/trigger_update_orderitem_remove.sql"))
          .data());

  QSqlQuery q00(
      QString("DROP TRIGGER IF EXISTS `%1update_orderitem_status_add`;")
          .arg(_prefix),
      _db);
  if (q00.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q00.lastError().text());
    return false;
  }

  QSqlQuery q01(trigger1.arg(_prefix), _db);
  if (q01.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q01.lastError().text());
    return false;
  }

  QSqlQuery q02(
      QString("DROP TRIGGER IF EXISTS `%1update_orderitem_status_remove`;")
          .arg(_prefix),
      _db);
  if (q02.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q02.lastError().text());
    return false;
  }
  QSqlQuery q03(trigger2.arg(_prefix), _db);
  if (q03.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q03.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------
