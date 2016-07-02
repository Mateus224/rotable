#ifndef EXECUTOR_H
#define EXECUTOR_H

//------------------------------------------------------------------------------

#include "configadmin.h"
#include "tcpclient.h"
#include "compackage.h"
#include "serverloglistener.h"

#include <QObject>

//------------------------------------------------------------------------------

namespace rotable {
  class ImageContainer;
  class ProductContainer;
}

class MainWindow;

//------------------------------------------------------------------------------

class Executor : public QObject
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param mainwindow      mainwindow
   * @param configFilePath  path to config file
   * @param parent          parent object
   */
  explicit Executor(MainWindow* mainwindow, const QString &configFilePath,
                    QObject *parent = 0);

  /**
   * Set the image container.
   *
   * @param images          image container
   */
  void setImageContainer(rotable::ImageContainer* images);

  /**
   * Set the product container.
   *
   * @param products              product container
   */
  void setProductContainer(rotable::ProductContainer* products);

signals:
  void connectionEstablished();
  void connectionLost();
  void serverLogConnectionEstablished();
  void serverLogConnectionLost();
  void statusMessage(QString text);
  void serverLog(rotable::LogManager::LogMessage message);

  void categoryReceived(rotable::ProductCategory* category);

  void onLicenceStatus(const QString& string);
  void onLicenceConfig(const QString& string);

  void updateSequenceProduct(int);
  void updateSequenceCategory(int);

public slots:
  /**
   * Connect to rotable server.
   */
  void onConnectToServer();

  /**
   * Disconnect from Server
   */
  void onDisconnectFromServer();

  /**
   * Button to add a new product category has been clicked.
   */
  void onAddProductCategory();

  /**
   * Category has been updated.
   *
   * @param category      updated category
   */
  void onUpdateCategory(rotable::ProductCategory* category);

  /**
   * Button to add a new product has been clicked.
   */
  void onAddProduct();

  /**
   * Product has been updated.
   *
   * @param product       updated product
   */
  void onUpdateProduct(rotable::Product* product);

  /**
   * Button to reset the complete database has been clicked.
   */
  void onResetDatabase();

  /**
   * Button to export the database has been clicked.
   */
  void onExportDatabase();

  /**
   * Button to import the database has been clicked.
   */
  void onImportDatabase();

  /**
   * Button to remove the currently selected product or category has been clicked.
   */
  void onRemoveCurrentEntry();

  /**
   * Button to rename the currently selected product or category has been clicked.
   */
  void onRenameCurrentEntry();

  /**
   * The category selection in the category list view has been changed.
   *
   * @param id              selected category id
   *                        -1 on no selection
   */
  void onCategorySelectionChanged(int id);

  /**
   * The product selection in the product table view has been changed.
   *
   * @param id              selected product id
   *                        -1 on no selection
   */
  void onProductSelectionChanged(int id);

  /**
   * The user wants to export his current statistics.
   */
  void onExportStatistic();

  /**
   * The user wants to clear the log of server messages.
   */
  void onClearDebugServerLog();

  /**
   * The user wants to start listening on server logs.
   */
  void onStartDebugServerListening();

  /**
   * The user wants to stop listening on server logs.
   */
  void onStopDebugServerListening();

  /**
   * Method for send new licence to server
   */
  void onAddLicence();


private slots:
  void onClientError(QAbstractSocket::SocketError error);

  void onConnectionEstablished();
  void onConnectionLost();

  void onPackageReceived(rotable::ComPackage* package);

private:
  void requestCategoryIds();
  void requestProductIds(int categoryId);
  void requestCategory(int categoryId);
  void requestProduct(int productId);
  void requestServerConfigs();
  void requestLicenceStatus();

  void dataReturned(rotable::ComPackageDataReturn* package);
  void dataChanged(rotable::ComPackageDataChanged* package);

  void loadServerConfigs(const QString& path);
  void loadLicenceStatus(const QString& status);

  /* MainWindow object */
  MainWindow* _mainwindow;

  /* Config object */
  ConfigAdmin _config;

  /* TCP client for connection to the server */
  TcpClient _tcp_client;

  QString _username;
  QString _password;

  /* Whether the user clicked disconnect (Avoid notification in that case) */
  bool _disconnectRequested;

  /* Currently pending data requests */
  QMap<QString, rotable::ComPackageDataRequest*> _dataRequest;

  /* Images */
  rotable::ImageContainer* _images;

  /* Products and categories */
  rotable::ProductContainer* _products;

  rotable::ProductCategory* _selectedCategory;
  rotable::Product* _selectedProduct;

  ServerLogListener _serverLogListener;
}; // class Executor

//------------------------------------------------------------------------------

#endif // EXECUTOR_H
