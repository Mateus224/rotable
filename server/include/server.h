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
   * Execute a command received from a client.
   *
   * @param package     command package
   * @return            true on success
   */
  bool executeCommand(ComPackageCommand* package);

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
}; // class Server

//------------------------------------------------------------------------------

#endif // ROTABLE_SERVER_H
