#ifndef ROTABLE_SERVER_H
#define ROTABLE_SERVER_H

//------------------------------------------------------------------------------

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QSTRING_H
#include <QString>
#endif

#include "configserver.h"
#include "tcpserver.h"
#include "database.h"
#include "settings.h"
#include "compackage.h"
#include "config.h"
#include "schedule.h"

//------------------------------------------------------------------------------

namespace rotable {
  class Server;
}

//------------------------------------------------------------------------------

/**
 * Server logic
 */
class rotable::Server : public QObject
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param configFilePath      path to config file
   * @param parent              parent object
   */
  Server(const QString& configFilePath = QString("config.ini"),
         QObject *parent = 0);

  /**
   * Destructor
   */
  ~Server();

  /**
   * Startup server.
   *
   * @return                  false on critical errors
   */
  bool startup();

  /**
   * Create a new empty database.
   */
  void createDatabase();

private slots:
  /**
   * A client has been connected.
   *
   * @param client      client id
   */
  void clientConnected(client_t client);

  /**
   * A package from a client has been received.
   *
   * @param client      client id
   * @param package     package
   */
  void packageReceived(client_t client, ComPackage* package);

  /**
   * A client has been disconnected.
   * (The client id is now invalid!)
   *
   * @param client      client id (now invalid)
   * @param clientName  client name
   */
  void clientDisconnected(client_t client, const QString& clientName);

private:
  /**
   * Create data return package for a data request.
   *
   * @param request     request
   * @return            0 if data was not found
   */
  ComPackageDataReturn* getData(ComPackageDataRequest* request);

  /**
   * Set data received by a data set package.
   *
   * @param set         data set package
   * @return            false, if client was not allowed to set this data
   *                    or something failed during the process
   */
  bool setData(ComPackageDataSet* set);

  /**
   * Add a new product category to the database.
   * (Will automatically inform all connected clients)
   *
   * @param pc          new product category
   * @return            true on success
   */
  bool addCategory(ProductCategory* category);

  /**
   * Update an existing product category.
   * (Will automatically inform all connected clients)
   *
   * @param pc          product category to update
   * @return            true on success
   */
  bool updateCategory(ProductCategory* category);

  /**
   * Add a new product to the database.
   * (Will automatically inform all connected clients)
   *
   * @param pc          new product
   * @return            true on success
   */
  bool addProduct(Product* product);

  /**
   * Update an existing product.
   * (Will automatically inform all connected clients)
   *
   * @param pc          product to update
   * @return            true on success
   */
  bool updateProduct(Product* product);

  /**
   * Add a new income to database
   * Only use for server propose
   * @param income      new income
   * @return            true on success
   */
  bool addIncome(Income *income);

  /**
   * Update an existing income
   * Only use for server propose
   * @param income      income to update
   * @return            true on success
   */
  bool updateIncome(Income *income);

  /**
   * Create new income, base on actual date and last income
   * Used by ScheduleOperation
   * @return            teue on success
   */
  bool newIncome();

  /**
   * Execute a command received from a client.
   *
   * @param package     command package
   * @return            true on success
   */
  bool executeCommand(ComPackageCommand* package);

  /**
   * Prosses login package, then login in property way
   *
   * @param package     login package
   * @param client      client socket, use to save to table with
   * @return            ComPackageDataReturn with account information
   */
  ComPackageDataReturn *login(ComPackageLogin* package, client_t client);

  /**
   * Method to send package to all waiters
   *
   * @param package     Package with data to send
   */
  inline void send_to_waiters(ComPackage &package);

  /**
   * Load config from database
   */
  void load_configs();

  /**
   * Realized config
   *
   * @param config      config class
   */
  void config_parser(Config *config);

  /**
   * Method prepare ScheduleOperation object and add this to Schedule
   * @param config      Config
   */
  void day_begin_config(Config *config);

  /* Configuration file access */
  ConfigServer _config;

  /* TCP-Server object */
  TcpServer _tcp;

  /* Database connection */
  Database _db;

  /**
   * Image path to object mapping.
   */
  struct Image {
    QString path;
    QImage img;
  };

  /* Images */
  QMap<QString, Image> _images;

  /**
   * client_t - socket
   * int - waiter id
   * Map with sockets on with connected are waiters
   * With that we can send information to any/all waiter(s)
   */
  QMap<client_t, int> _waiters;
  QList<Config*> cfg_list;
  Schedule* schedule;

}; // class Server

//------------------------------------------------------------------------------

#endif // ROTABLE_SERVER_H
