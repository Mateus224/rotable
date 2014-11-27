#include "private/precomp.h"

#include "database.h"
#include "settings.h"

#include <QSqlDriver>

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

static const char S_createCategoriesTable[] =
    "CREATE TABLE IF NOT EXISTS `%1categories` ("
    "  `id` INTEGER PRIMARY KEY AUTOINCREMENT,"
    "  `name` VARCHAR(512) NOT NULL,"
    "  `icon` VARCHAR(128) NOT NULL"
    ");";

static const char S_createProductsTable[] =
    "CREATE TABLE IF NOT EXISTS `%1products` ("
    "  `id` INTEGER PRIMARY KEY AUTOINCREMENT,"
    "  `name` VARCHAR(512) NOT NULL,"
    "  `price` INTEGER NOT NULL,"
    "  `info` text NOT NULL,"
    "  `category_id` INTEGER NOT NULL,"
    "  `icon` VARCHAR(128) NOT NULL,"
    "  `amount` VARCHAR(512) NOT NULL"
    ");";

static const char S_insertCategory[] =
    "INSERT INTO `%1categories` "
    "(`id`, `name`, `icon`) "
    "VALUES (%2, %3, %4);";

static const char S_insertProduct[] =
    "INSERT INTO `%1products` "
    "(`id`, `name`, `price`, `info`, `category_id`, `icon`, `amount`) "
    "VALUES (%2, %3, %4, %5, %6, %7, %8);";

static const char S_selectCategory[] =
    "SELECT %2 FROM %1categories WHERE `%3` = %4";

static const char S_selectProduct[] =
    "SELECT %2 FROM %1products WHERE `%3` = %4";

static const char S_selectAllCategoryIds[] =
    "SELECT `id` FROM `%1categories`";

static const char S_selectAllProductIds[] =
    "SELECT `id` FROM `%1products`";

static const char S_updateCategory[] =
    "UPDATE `%1categories` SET `name` = :name, `icon` = :icon WHERE `id` = %2;";

static const char S_updateProduct[] =
    "UPDATE `%1products` SET `name` = :name, `price` = :price, "
    "`info` = :info, `category_id` = :category_id, `amount` = :amount, `icon` = :icon "
    "WHERE `id` = %2;";

static const char S_deleteProduct[] =
    "DELETE FROM `%1products` WHERE `id` = %2;";

static const char S_deleteProductsOfCategory[] =
    "DELETE FROM `%1products` WHERE `category_id` = %2;";

static const char S_deleteCategory[] =
    "DELETE FROM `%1categories` WHERE `id` = %2;";

//------------------------------------------------------------------------------

Database::Database(QObject *parent) :
  QObject(parent), _connected(false)
{

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

  QString queryStr = QString(S_selectAllCategoryIds).arg(_prefix);

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
    queryStr = QString(S_selectAllProductIds).arg(_prefix);
  } else {
    queryStr = QString(S_selectProduct)
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

ProductCategory* Database::category(int id)
{
  if (!isConnected()) {
    return 0;
  }

  QString queryStr = QString(S_selectCategory).arg(_prefix, "*", "id").arg(id);

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

  QString queryStr = QString(S_selectProduct).arg(_prefix, "*", "id").arg(id);

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

bool Database::addCategory(ProductCategory* category)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr = QString(S_insertCategory).arg(_prefix, "NULL", ":name", ":icon");

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

  QString queryStr = QString(S_insertProduct)
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

bool Database::updateCategory(ProductCategory *category)
{
  if (!isConnected()) {
    return false;
  }

  QString queryStr = QString(S_updateCategory).arg(_prefix).arg(category->id());

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

  QString queryStr = QString(S_updateProduct).arg(_prefix).arg(product->id());

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
    QString queryStr = QString(S_deleteCategory).arg(_prefix).arg(id);

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

  QString queryStr = QString(S_deleteProduct).arg(_prefix).arg(id);

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

  QSqlQuery q1(QString("DROP TABLE IF EXISTS `%1categories`;").arg(_prefix), _db);
  if (q1.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q1.lastError().text());
    return false;
  }

  QSqlQuery q2(QString("DROP TABLE IF EXISTS `%1products`;").arg(_prefix), _db);
  if (q2.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q2.lastError().text());
    return false;
  }

  QSqlQuery q3(QString(S_createCategoriesTable).arg(_prefix), _db);
  if (q3.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q3.lastError().text());
    return false;
  }

  QSqlQuery q4(QString(S_createProductsTable).arg(_prefix), _db);
  if (q4.lastError().type() != QSqlError::NoError) {
    qCritical() << tr("Query exec failed: %1").arg(q4.lastError().text());
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

  dest += QString("DROP TABLE IF EXISTS `%1categories`;\n").arg(_prefix);
  dest += QString("DROP TABLE IF EXISTS `%1products`;\n").arg(_prefix);

  dest += QString(S_createCategoriesTable).arg(_prefix) + '\n';
  dest += QString(S_createProductsTable).arg(_prefix) + '\n';

  QList<int> ids;
  if (categoryIds(ids)) {
    for (int i = 0; i < ids.size(); ++i) {
      ProductCategory* c = category(ids[i]);
      if (c) {
        dest += QString(S_insertCategory)
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

  ids.clear();
  if (productIds(ids, -1)) {
    for (int i = 0; i < ids.size(); ++i) {
      Product *p = product(ids[i]);
      if (p) {
        dest += QString(S_insertProduct)
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

  QString queryStr = QString(S_selectCategory)
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

  QString queryStr = QString(S_selectCategory)
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

  QString queryStr = QString(S_selectProduct)
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

  QString queryStr = QString(S_selectProduct)
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

bool Database::isConnected() const
{
  if (_connected) {
    return _db.isOpen();
  }
  return false;
}
