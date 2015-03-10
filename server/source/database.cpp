#include "private/precomp.h"

#include "database.h"
#include "settings.h"
#include "order.h"

#include <QSqlDriver>
#include <QSqlRecord>

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

static const char S_deleteProductsOfCategory[] =
    "DELETE FROM `%1products` WHERE `category_id` = %2;";

//------------------------------------------------------------------------------

Database::Database(QObject *parent) :
  QObject(parent), _connected(false)
{
  
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

  SqlCommands waiterCmds;
  collectSqlCommands(waiterCmds, "waiters");
  _sqlCommands.append(waiterCmds);
}

//------------------------------------------------------------------------------

bool Database::startConnection(const QString& driver,
                               const QString& host, const QString& database,
                               const QString& user, const QString& pass,
                               const QString& prefix)
{
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

bool Database::categoryIds(QList<int>& ids)
{
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Categories]._listIds.arg(_prefix);

  QSqlQuery q(_db);
  //q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  if (!q.exec()) {
    qCritical() << tr("Query exec failed: (%1: %2")
                   .arg(queryStr, q.lastError().text());
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

bool Database::productIds(QList<int>& ids, int categoryId)
{
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr;
  if (categoryId == -1) {
    queryStr = _sqlCommands[Products]._listIds.arg(_prefix);
  } else {
    queryStr = _sqlCommands[Products]._select
               .arg(_prefix, "`id`", "category_id").arg(categoryId);
  }

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

bool Database::orderIds(QList<int>& ids, int clientId)
{
  ids.clear();

  if (!isConnected()) {
    return false;
  }

  QString queryStr;
  if (clientId == -1) {
    queryStr = _sqlCommands[Orders]._listIds.arg(_prefix);
  } else {
    queryStr = _sqlCommands[Orders]._select
               .arg(_prefix, "`id`", "client_id").arg(clientId);
  }

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

ProductCategory* Database::category(int id)
{
  if (!isConnected()) {
    return 0;
  }

  QString queryStr = _sqlCommands[Categories]._select.arg(_prefix, "*", "id").arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical() << tr("Query exec failed: (%1: %2")
                   .arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical() << tr("Query: returned %1 results but we expected it to return 1!")
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
    qDebug() << tr("Could not convert '%1' to integer!").arg(q.value("id").toString());
    return 0;
  }

  ProductCategory* c = new ProductCategory();
  c->setName(q.value("name").toString());
  c->setIcon(q.value("icon").toString());
  c->setId(category_id);

  return c;
}

//------------------------------------------------------------------------------

Product* Database::product(int id)
{
  if (!isConnected()) {
    return 0;
  }

  QString queryStr = _sqlCommands[Products]._select.arg(_prefix, "*", "id").arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical() << tr("Query exec failed: (%1: %2")
                   .arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical() << tr("Query: returned %1 results but we expected it to return 1!")
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
    qCritical() << tr("Could not convert '%1' to integer!").arg(q.value("id").toString());
    return 0;
  }

  int categoryId = q.value("category_id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!").arg(q.value("category_id").toString());
    return 0;
  }

  int price = q.value("price").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!").arg(q.value("price").toString());
    return 0;
  }


  Product* p = new Product();

  p->setName(q.value("name").toString());
  p->setIcon(q.value("icon").toString());
  p->setInfo(q.value("info").toString());
  p->setAmount(q.value("amount").toString());
  p->setCategoryId(categoryId);
  p->setId(productId);
  p->setPrice(price);

  return p;
}

//------------------------------------------------------------------------------

Order*Database::order(int id)
{
  if (!isConnected()) {
    return 0;
  }

  QString queryStr = _sqlCommands[Orders]._select.arg(_prefix, "*", "id").arg(id);

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return 0;
  }

  if (!q.exec()) {
    qCritical() << tr("Query exec failed: (%1: %2")
                   .arg(queryStr, q.lastError().text());
    return 0;
  }

  if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
    if (q.size() != 1) {
      qCritical() << tr("Query: returned %1 results but we expected it to return 1!")
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
    qCritical() << tr("Could not convert '%1' to integer!").arg(q.value("id").toString());
    return 0;
  }

  int clientId = q.value("client_id").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!").arg(q.value("client_id").toString());
    return 0;
  }

  int state = q.value("stat").toInt(&ok);
  if (!ok) {
    qCritical() << tr("Could not convert '%1' to integer!").arg(q.value("state").toString());
    return 0;
  }

  QDateTime orderSent = q.value("date_added").toDateTime();

  Order* o = new Order();

  o->setId(orderId);
  o->setClientId(clientId);
  o->setState(state);

  // TODO: continue here

  return o;
}

Waiter *Database::waiter(int id)
{
    if (!isConnected()) {
      return 0;
    }

    QString queryStr = _sqlCommands[Waiters]._select.arg(_prefix, "*", "id").arg(id);

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return 0;
    }

    if (!q.exec()) {
      qCritical() << tr("Query exec failed: (%1: %2")
                     .arg(queryStr, q.lastError().text());
      return 0;
    }

    if (_db.driver()->hasFeature(QSqlDriver::QuerySize)) {
      if (q.size() != 1) {
        qCritical() << tr("Query: returned %1 results but we expected it to return 1!")
                       .arg(q.size());
        return 0;
      }
    }

    if (!q.next()) {
      return 0;
    }

    bool ok;
    int waiterId = q.value("id").toInt(&ok);
    if (!ok) {
      qCritical() << tr("Could not convert '%1' to integer!").arg(q.value("id").toString());
      return 0;
    }

    QString passwd = q.value("passwd").toString();
    QString nick = q.value("nick").toString();
    QString name = q.value("name").toString();

    Waiter* w = new Waiter();

    w->setId(waiterId);
    w->setHashPassword(passwd);
    w->setNick(nick);
    w->setName(name);

    return w;
}

//------------------------------------------------------------------------------

bool Database::addCategory(ProductCategory* category)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Categories]._insert.arg(_prefix, "NULL", ":name", ":icon");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", category->name());
  q.bindValue(":icon", category->icon());

  if (!q.exec()) {
    qCritical() << tr("Query exec failed: (%1: %2")
                   .arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::addProduct(Product* product)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Products]._insert
                     .arg(_prefix, "NULL", ":name", ":price", ":info", ":category_id", ":icon", ":amount");

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

  if (!q.exec()) {
    qCritical() << tr("Query exec failed: (%1: %2")
                   .arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::addWaiter(Waiter* waiter)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Waiters]._insert
                     .arg(_prefix, "NULL", ":nick", ":name", ":passwd");

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", waiter->name());
  q.bindValue(":nick", waiter->nick());
  q.bindValue(":passwd", waiter->hashPassword());

  if (!q.exec()) {
    qCritical() << tr("Query exec failed: (%1: %2")
                   .arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::updateCategory(ProductCategory *category)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Categories]._update.arg(_prefix).arg(category->id());

  QSqlQuery q(_db);
  q.setForwardOnly(true);

  if (!q.prepare(queryStr)) {
    qCritical() << tr("Invalid query: %1").arg(queryStr);
    return false;
  }

  q.bindValue(":name", category->name());
  q.bindValue(":icon", category->icon());

  if (!q.exec()) {
    qCritical() << tr("Query exec failed: (%1: %2")
                   .arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::updateProduct(Product *product)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Products]._update.arg(_prefix).arg(product->id());

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

  if (!q.exec()) {
    qCritical() << tr("Query exec failed: (%1: %2")
                   .arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::removeCategory(int id)
{
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

bool Database::removeProduct(int id)
{
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
    qCritical() << tr("Query exec failed: (%1: %2")
                   .arg(queryStr, q.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::createDatabase()
{
  if (!isConnected()) {
    return false;
  }

  // Set time zone is not available when using SQLITE
  //ret &= dbExec(QString("SET time_zone = \"%1\";").arg(ROTABLE_DATABASE_TIMEZONE));

  // Category table
  QSqlQuery q1(QString("DROP TABLE IF EXISTS `%1categories`;").arg(_prefix), _db);
  if (q1.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q1.lastError().text());
    return false;
  }

  QSqlQuery q2(_sqlCommands[Categories]._create.arg(_prefix), _db);
  if (q2.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q2.lastError().text());
    return false;
  }

  // Product table
  QSqlQuery q3(QString("DROP TABLE IF EXISTS `%1products`;").arg(_prefix), _db);
  if (q3.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q3.lastError().text());
    return false;
  }

  QSqlQuery q4(_sqlCommands[Products]._create.arg(_prefix), _db);
  if (q4.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q4.lastError().text());
    return false;
  }

//  That table don't exists (don't exist in sql commands, don't create in other way)
//  QSqlQuery q5(QString("DROP TABLE IF EXISTS `%1tables`;").arg(_prefix), _db);
//  if (q5.lastError().type() != QSqlError::NoError) {
//    qCritical() << tr("Query exec failed: %1").arg(q5.lastError().text());
//    return false;
//  }

  // Client table
  QSqlQuery q5(QString("DROP TABLE IF EXISTS `%lclient`;").arg(_prefix), _db);
  if (q5.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q5.lastError().text());
    return false;
  }

  QSqlQuery q6(_sqlCommands[Clients]._create.arg(_prefix), _db);
  if (q6.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q6.lastError().text());
    return false;
  }

  // Waiter table
  QSqlQuery q7(QString("DROP TABLE IF EXISTS `%1waiters`;").arg(_prefix), _db);
  if (q7.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q7.lastError().text());
    return false;
  }

  QSqlQuery q8(_sqlCommands[Waiters]._create.arg(_prefix), _db);
  if (q8.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q8.lastError().text());
    return false;
  }

  // Order table
  QSqlQuery q9(QString("DROP TABLE IF EXISTS `%1order`;").arg(_prefix), _db);
  if (q9.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q9.lastError().text());
    return false;
  }

  QSqlQuery q10(_sqlCommands[Orders]._create.arg(_prefix), _db);
  if (q10.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q10.lastError().text());
    return false;
  }
  // Order_item table
  QSqlQuery q11(QString("DROP TABLE IF EXISTS `%1order_items`;").arg(_prefix), _db);
  if (q11.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q11.lastError().text());
    return false;
  }

  QSqlQuery q12(_sqlCommands[OrderItems]._create.arg(_prefix), _db);
  if (q12.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q12.lastError().text());
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Database::exportDatabase(const QString& path, bool binary)
{
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

bool Database::exportDatabase(QString &dest)
{
  if (!isConnected()) {
    return false;
  }

  // Add drop table commands
  dest += QString("DROP TABLE IF EXISTS `%1categories`;\n").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1products`;\n").arg(_prefix);
  // TODO: chceck is it need'ed
  // dest += QString("DROP TABLE IF EXISTS `%1tables`;").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1waiters`;").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1clients`;").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1order`;").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1order_item`;").arg(_prefix);

  // Add create table command
  dest += _sqlCommands[Categories]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[Products]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[Clients]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[Waiters]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[Orders]._create.arg(_prefix) + '\n';
  dest += _sqlCommands[OrderItems]._create.arg(_prefix) + '\n';

  //-------------------------------------------------------------------------------
  // Add insert command with data
  //-------------------------------------------------------------------------------
  // Category
  QList<int> ids;
  if (categoryIds(ids)) {
    for (int i = 0; i < ids.size(); ++i) {
      ProductCategory* c = category(ids[i]);
      if (c) {
        dest += _sqlCommands[Categories]._insert
                .arg(_prefix)
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
        dest += _sqlCommands[Products]._insert
                .arg(_prefix)
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
  //TODO: export Waiter table
  //TODO: export Client table
  //TODO: export Order table
  //TODO: export OrderList table
  return true;
}

//------------------------------------------------------------------------------

bool Database::databaseExists() const
{
  if (!isConnected()) {
    return false;
  }

  QStringList tables = _db.tables(QSql::Tables);

  foreach (QString t, tables) {
    qDebug() << t;
  }

  if (tables.contains(QString("%1categories").arg(_prefix))
      && tables.contains(QString("%1products").arg(_prefix)))
  {
    return true;
  } else {
    return false;
  }
}

//------------------------------------------------------------------------------

bool Database::hasCategory(const QString &name)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Categories]._select
                     .arg(_prefix, "`id`", "name", QString("'%1'").arg(name));

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

  return q.next();
}

//------------------------------------------------------------------------------

bool Database::hasCategory(int id)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr = _sqlCommands[Categories]._select
                     .arg(_prefix, "`id`", "id", QString("'%1'").arg(id));

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

  return q.next();
}

//------------------------------------------------------------------------------

bool Database::hasProduct(const QString &name, int categoryId)
{
  if (!isConnected() || name.isEmpty() || categoryId == -1) {
    return false;
  }

  QString queryStr = _sqlCommands[Products]._select
                     .arg(_prefix, "`id`", "name", QString("'%1'").arg(name));
  queryStr += QString(" AND `category_id` = %1").arg(categoryId);

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

  return q.next();
}

//------------------------------------------------------------------------------

bool Database::hasProduct(int productId, int categoryId)
{
  if (!isConnected() || productId == -1 || categoryId == -1) {
    return false;
  }

  QString queryStr = _sqlCommands[Products]._select
                     .arg(_prefix, "`name`", "id", QString("'%1'").arg(productId));
  queryStr += QString(" AND `category_id` = %1").arg(categoryId);

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

  return q.next();
}

//------------------------------------------------------------------------------

int Database::hasWaiter(const QString nick, const QString passwdhash)
{
    if (!isConnected() || !nick.isEmpty() || !passwdhash.isEmpty()) {
      return false;
    }

    QString queryStr = _sqlCommands[Waiters]._select
                       .arg(_prefix, "`id`", "nick",QString("'%1'").arg(nick));
    queryStr += QString(" AND `passwd` = %1").arg(passwdhash);

    QSqlQuery q(_db);
    q.setForwardOnly(true);

    if (!q.prepare(queryStr)) {
      qCritical() << tr("Invalid query: %1").arg(queryStr);
      return -1;
    }

    if (!q.exec()) {
      qCritical() << tr("Query exec failed: (%1: %2")
                     .arg(queryStr, q.lastError().text());
      return -1;
    }

    if(q.next())
    {
        QSqlRecord rec = q.record();

        return rec.value(rec.indexOf("id")).toInt();
    }

    return -1;
}

//------------------------------------------------------------------------------

bool Database::isConnected() const
{
  if (_connected) {
    return _db.isOpen();
  }
  return false;
}

//------------------------------------------------------------------------------

void Database::collectSqlCommands(Database::SqlCommands& cmds, QString table)
{
  cmds._create = QString((const char*)QResource(
                           QString("://sql-commands/%1_create.sql").arg(table)).data());
  cmds._select = QString((const char*)QResource(
                           QString("://sql-commands/%1_select.sql").arg(table)).data());
  cmds._update = QString((const char*)QResource(
                           QString("://sql-commands/%1_update.sql").arg(table)).data());
  cmds._insert = QString((const char*)QResource(
                           QString("://sql-commands/%1_insert.sql").arg(table)).data());
  cmds._listIds = QString((const char*)QResource(
                            QString("://sql-commands/%1_select_ids.sql").arg(table)).data());
  cmds._remove = QString((const char*)QResource(
                           QString("://sql-commands/%1_remove.sql").arg(table)).data());

  Q_ASSERT(!cmds._create.isEmpty());
  Q_ASSERT(!cmds._select.isEmpty());
  Q_ASSERT(!cmds._update.isEmpty());
  Q_ASSERT(!cmds._insert.isEmpty());
  Q_ASSERT(!cmds._listIds.isEmpty());
  Q_ASSERT(!cmds._remove.isEmpty());
}
