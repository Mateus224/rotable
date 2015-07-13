#ifndef ROTABLE_DATABASE_H
#define ROTABLE_DATABASE_H

//------------------------------------------------------------------------------

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QSQLDATABASE_H
#include <QSqlDatabase>
#endif

#ifndef QSTRING_H
#include <QString>
#endif

#ifndef QMAP_H
#include <QMap>
#endif

#ifndef QJSONOBJECT_H
#include <QJsonObject>
#endif

#include "productcategory.h"
#include "product.h"
#include "order.h"
#include "compackage.h"
#include "client.h"
#include "income.h"
#include "config.h"
#include "productorder.h"

//------------------------------------------------------------------------------

namespace rotable {
class Database;
}

//------------------------------------------------------------------------------

/**
 * The Database class can connect to a database and read all categories
 * and products.
 *
 * This abstraction allows an easy replacing of the underlying database.
 */
class rotable::Database : public QObject
{
  Q_OBJECT

private:
  /**
   * Database tables
   */
  enum DatabaseTables {
    Categories = 0,
    Products,
    Clients,
    Orders,
    OrderItems,
    Waiters,
    Incomes,
    Configs,
    Passwords,
    MacAdresses
  };

  /**
   * Collection of sql commands for a table.
   */
  struct SqlCommands {
    QString _create;
    QString _select;
    QString _update;
    QString _insert;
    QString _listIds;
    QString _remove;
  };

public:
  /**
   * Constructor
   *
   * @param parent      parent object
   */
  Database(QObject *parent = 0);

  /**
   * Connect to the database.
   *
   * @param driver      database driver
   * @param host        host
   * @param database    database name
   * @param user        user name
   * @param pass        user password
   * @param prefix      table prefix
   * @return            true, if connection has been established
   */
  bool startConnection(const QString& driver,
                       const QString& host, const QString& database,
                       const QString& user, const QString& pass,
                       const QString& prefix);

  /**
   * Get list of category ids.
   *
   * @param ids         (result) list of category ids
   * @return            true on successs
   */
  bool categoryIds(QList<int>& ids);

  /**
   * Get list of product ids.
   *
   * @param ids         (result) list of product ids
   * @param categoryId  category id (-1 for all categories)
   * @return            true on success
   */
  bool productIds(QList<int>& ids, int categoryId);

  /**
   * Get list of order ids.
   *
   * @param ids         (result) list of order ids
   * @param clientId    client id (-1 for all orders)
   * @return            true on success
   */
  bool orderIds(QList<int>& ids, int clientId);

  /**
   * Get list of config ids
   *
   * @param ids (result) list of config ids
   * @return true on success
   */
  bool configIds(QList<int>& ids);

  /**
   * Read category from database.
   *
   * @param id          category id
   * @return            category or NULL on error
   */
  ProductCategory *category(int id);

  /**
   * Read product from database.
   *
   * @param id          product id
   * @return            product or NULL on errror
   */
  Product *product(int id);

  /**
   * Read order from database.
   *
   * @param id          order id
   * @return            order or NULL on error
   */
  Order *order(int id);

  /**
   * Read waiter from database.
   * @param id          waiter id
   * @return            waiter or NULL on error
   */
  Waiter *waiter(int id);

  /**
   * Read income from database
   *
   * @param id          income id
   * @return            income or NULL on error
   */
  Income *income(int id);

  /**
   * Read config from database
   *
   * @param id          config id
   * @return            config or NULL on error
   */

  Config *config(int id);

  /**
   * Add a new product category to the database.
   * (Will not check whether a category with this name already exists!)
   *
   * @param category    new category
   * @return            true on success
   */
  bool addCategory(ProductCategory* category);

  /**
   * Add a new product to the database.
   * (Will not check whether a product with this name already exists!)
   *
   * @param product     new product
   * @param categoryId  category id
   * @return            true on success
   */
  bool addProduct(Product* product);

  /**
   * Add a new user to the database.
   *
   * @param user        new user
   * @return            true on success
   */
  bool addUser(User* user);

  /**
   * Add new income record to the database
   *
   * @param income      new income
   * @return            true on succes
   */
  bool addIncome(Income *income);

  /**
   * Add new config record to the database
   *
   * @param config      new config
   * @return            true on success
   */
  bool addConfig(Config *config);

  /**
   * Add new order to the database
   *
   * @param order       new order
   * @return            true on success
   */
  bool addOrder(Order *order);

  /**
   * Update a product category.
   *
   * @param category    product category
   * @return            true on success
   */
  bool updateCategory(ProductCategory* category);

  /**
   * Update a product.
   *
   * @param product     product
   * @return            true on success
   */
  bool updateProduct(Product* product);

  /**
   * Update dayly income
   * @param income      Update income object
   * @return            true on success
   */
  bool updateIncome(Income *income);

  /**
   * Update config record
   *
   * @param config      Config object
   * @return            true on success
   */
  bool updateConfig(Config *config);


  bool updateOrders(QList<OrderItem *> order);


  /**
   * Remove a category.
   *
   * @param id          id of category
   * @return            true on success
   */
  bool removeCategory(int id);

  /**
   * Remove a product.
   *
   * @param id          id of product
   * @return            true on success
   */
  bool removeProduct(int id);

  /**
   * Remove income
   *
   * @param id          id of income
   * @return            true on success
   */
  bool removeIncome(int id);

  /**
   * Remove a config.
   *
   * @param id          id of config
   * @return            true on success
   */
  bool removeConfig(int id);

  /**
   * Setup the database.
   *
   * @return            true on success
   */
  bool createDatabase();

  /**
   * Export the database to given file.
   *
   * @param path        destination file path
   * @param binary      whether to save the database in compressed binary format
   * @return            true on success
   */
  bool exportDatabase(const QString& path, bool binary);

  /**
   * Export the database as SQL command to given string.
   *
   * @param dest        destination string
   * @return            true on success
   */
  bool exportDatabase(QString& dest);

  /**
   * Import database from given file.
   *
   * @param path        database file to import
   * @return            true on success
   */
  bool importDatabase(const QString& path);

  /**
   * Check whether the database is already installed.
   *
   * @return            false if database not installed
   */
  bool databaseExists() const;

  /**
   * Check if a category with given name already exists.
   *
   * @param name        category name
   * @return            true if category already exists
   */
  bool hasCategory(const QString& name);
  bool hasCategory(int id);

  /**
   * Check if a product with given name already exists in given category.
   *
   * @param name        product name
   * @param categoryId  category id
   * @return            true if product already exists
   */
  bool hasProduct(const QString& name, int categoryId);
  bool hasProduct(int productId, int categoryId);

  /**
    Check if user exist
    require for login
   * @param nick        Waiter nick
   * @param passwdhash  password hash
   * @return            id if user with nick and password exists, otherwise -1
   */
  int hasUser(const QString &nick, const QString &passwdHash);

  /**
   * Check if income exist base on date
   * @param date        date
   * @return            id if exists, otherwise -1
   */
  int hasIncome(QDate date);

  /**
   * Get list of income base on mounth and year
   * @param mounth      mounth
   * @param year        year
   * @return            id lists if exists, otherwise NULL
   */
  QList<int> *hasIncome(int mounth, int year);

  /**
   * Check if income exist base on id
   * @param id          income id
   * @return            id if exists, otherwise -1
   */
  int hasIncome(int id);

  Income* getLastIncome();
  int getLastIncomeId();
  /**
   * Check Config record exist
   * @param name        config name
   * @return            record id
   */
  int hasConfigName(int name);

  /**
   * Check Config record exist
   * @param id          record id
   * @return            true on success
   */
  bool hasConfig(int id);

  /**
   * Get id of MacAddress if exists
   * @param macAdresses
   * @return            id or -1
   */
  int hasMacAddress(QString macAdresses);

  /**
   * Check whether this object is connected to the database.
   *
   * @return            true if connected
   */
  bool isConnected() const;

  /**
   * Add initial data to database
   * @return    true on success
   */
  bool add_init_data();

  /**
   * Register table
   * @return            table id
   */
  int registerTable(QString name, QString macAdresses);

signals:
  void parseConfig(Config* c);

private:
  /**
   * Collect SQL commands from resource file.
   *
   * @param cmds        collected commands
   */
  void collectSqlCommands(SqlCommands& cmds, QString table);


  /* Database handle */
  QSqlDatabase _db;

  /* Database table prefix */
  QString _prefix;

  /* Whether this object is connected to the database */
  bool _connected;

  QList<SqlCommands> _sqlCommands;
}; // class Database

//------------------------------------------------------------------------------

#endif // ROTABLE_DATABASE_H
