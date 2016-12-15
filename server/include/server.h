#ifndef ROTABLE_SERVER_H
#define ROTABLE_SERVER_H

//------------------------------------------------------------------------------

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QSTRING_H
#include <QString>
#endif
#include "filecontainer/file.h"
#include "compackage.h"
#include "config.h"
#include "configserver.h"
#include "database.h"
#include "schedule.h"
#include "settings.h"
#include "tcpserver.h"
//#include "licence.h"

//------------------------------------------------------------------------------

namespace rotable {
class Server;
}

//------------------------------------------------------------------------------

/**
 * Server logic
 */
class rotable::Server : public QObject {
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param configFilePath      path to config file
   * @param parent              parent object
   */
  Server(const QString &configFilePath = QString("config.ini"),
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
  void packageReceived(client_t client, ComPackage *package);

  /**
   * A client has been disconnected.
   * (The client id is now invalid!)
   *
   * @param client      client id (now invalid)
   * @param clientName  client name
   */
  void clientDisconnected(client_t client, const QString &clientName);

private:
  /**
   * Create data return package for a data request.
   *
   * @param request     request
   * @param client      request source
   * @return            0 if data was not found
   */
  ComPackageDataReturn *getData(ComPackageDataRequest *request, client_t client);

  /**
   * Set data received by a data set package.
   *
   * @param set         data set package
   * @return            false, if client was not allowed to set this data
   *                    or something failed during the process
   */
  bool setData(ComPackageDataSet *set, client_t client);

  /**
   * Add a new product category to the database.
   * (Will automatically inform all connected clients)
   *
   * @param pc          new product category
   * @return            true on success
   */
  bool addCategory(ProductCategory *category);

  /**
   * Update an existing product category.
   * (Will automatically inform all connected clients)
   *
   * @param pc          product category to update
   * @return            true on success
   */
  bool updateCategory(ProductCategory *category);

  /**
   * Update order
   *
   * @param order       order to update
   * @return
   */
  bool updateOrder(Order *order);

  /**
   * Create new order
   * @param ordes       List of item in order
   * @return            true on succes
   */
  bool newOrder(QList<OrderItem *> orders, int clientId);

  /**
   * Add a new product to the database.
   * (Will automatically inform all connected clients)
   *
   * @param pc          new product
   * @return            true on success
   */
  bool addProduct(Product *product);

  /**
   * Update an existing product.
   * (Will automatically inform all connected clients)
   *
   * @param pc          product to update
   * @return            true on success
   */
  bool updateProduct(Product *product);

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
   * @return            true on success
   */
  bool newIncome();

  /**
   * Close order after day is end
   *
   * @return            true on success
   */
  bool closeDay();

  /**
   * Set status Waiter need on table
   *
   * @param need        true if waiter is needed
   * @param tableId     table id
   *
   * @return            true on success
   */
  bool setWaiterNeed(bool need, int tableId);

  bool updateAdvertising(AdvertisingVideo *advertising);

  /**
   * Execute a command received from a client.
   *
   * @param package     command package
   * @return            true on success
   */
  bool executeCommand(ComPackageCommand *package);

  /**
   * Prosses login package, then login in property way
   *
   * @param package     login package
   * @param client      client socket, use to save to table with
   * @return            true on success
   */
  bool login(ComPackageConnectionRequest *package, client_t client);

  /**
   * Method to send package to connected users
   *
   * @param package         Package with data
   * @param accountType     Account type
   */
  inline void send_to_users(ComPackage &package, int accountType);

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

  /**
   * Load StateConfig settings to server
   * @param config      Config
   */
  void closeStateConfig(Config *config);

  /**
   * Prepre map with ComPackageMessage to send specific table
   * @return            QMap<tableId, package>
   */
  QMap<int, ComPackageMessage *> queueOrders();

  /**
   * Collect config and parse them to JSON object
   * @return            JSON object with config
   */
  QJsonValue configToJSON();

  /**
   * Send QueueMessage to connected client
   */
  void sendQueueOrders();

  /**
   * @brief typeOfFileDestination
   * @param package
   * @return true if package was stored and written in the database
   */
  bool typeOfFileDestination(ComPackageSendFile* package);

  /**
   * @brief addAdvertisingSD_Database
   * @param package
   * @return
   * Adding File on SD and in the Database.
   * if file exist in Medias/Files table but the row of this video is set on removed
   * than we undo this and we are setting it back to flase. Otherwise we store the
   * files which are new in a List.
   * In the next step we store the file data on the sd-card and we are adding the information into
   * Media/File table. In the last step we add with default values the information to the
   * advertising table. It doesn't metter if the media ID exist we add a new
   * advertising video. So we can have more than entrys in medias with the same media ID.
   * The current is still the max advertising ID.
   */
  bool addAdvertisingSD_Database(ComPackageSendFile* package);

  /**
   * @brief Removing File from the SD
   * @param id
   * @return
   */
  bool addAdvertisingSD_Database(int id);

  /**
   * @brief Check if connection was enstablished by admin account
   * @param connection connection to validate
   *
   * @return bool       true if it is a admin
   */
  bool ifAdmin(int connection) const;

  /**
   * @brief Update logged Waiter categories
   *
   * @param waiterId    waiter id
   * @param categoryId  category id
   * @param type        add category(1) or remove category(-1)
   */
  void updateWaiterCategories(int waiterId, int categoryId, int type);

  /* Configuration file access */
  rotable::ConfigServer _config;

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
  QMap<client_t, int> _users[3];

  /**
   * @Schedule object
   */
  rotable::Schedule *schedule;

  /**
   * List with waiters
   */
  QMap<client_t, Waiter*> _waiterList;

  /**
   * @brief _licence
   * Licence object
   */
  //  rotable::Licence* _licence;

  struct {
    QList<int> toChange; /**< TODO: describe */
    int newState; /**< TODO: describe */
  } _stateChange; /**< TODO: describe */

}; // class Server

//------------------------------------------------------------------------------

#endif // ROTABLE_SERVER_H
