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

/**
 * @brief
 *
 */
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
  /**
   * @brief
   *
   */
  void connectionEstablished();
  /**
   * @brief
   *
   */
  void connectionLost();
  /**
   * @brief
   *
   */
  void serverLogConnectionEstablished();
  /**
   * @brief
   *
   */
  void serverLogConnectionLost();
  /**
   * @brief
   *
   * @param text
   */
  void statusMessage(QString text);
  /**
   * @brief
   *
   * @param message
   */
  void serverLog(rotable::LogManager::LogMessage message);

  /**
   * @brief
   *
   * @param category
   */
  void categoryReceived(rotable::ProductCategory* category);

  /**
   * @brief
   *
   * @param string
   */
  void onLicenceStatus(const QString& string);
  /**
   * @brief
   *
   * @param string
   */
  void onLicenceConfig(const QString& string);

  /**
   * @brief
   *
   * @param int
   */
  void updateSequenceProduct(int);
  /**
   * @brief
   *
   * @param int
   */
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

  void onProductUp();
  /**
   * @brief
   *
   */
  void onProductDown();
  /**
   * @brief
   *
   */
  void onCategoryUp();
  /**
   * @brief
   *
   */
  void onCategoryDown();


private slots:
  /**
   * @brief
   *
   * @param error
   */
  void onClientError(QAbstractSocket::SocketError error);

  /**
   * @brief
   *
   */
  void onConnectionEstablished();
  /**
   * @brief
   *
   */
  void onConnectionLost();

  /**
   * @brief
   *
   * @param package
   */
  void onPackageReceived(rotable::ComPackage* package);

private:
  /**
   * @brief
   *
   */
  void requestCategoryIds();
  /**
   * @brief
   *
   * @param categoryId
   */
  void requestProductIds(int categoryId);
  /**
   * @brief
   *
   * @param categoryId
   */
  void requestCategory(int categoryId);
  /**
   * @brief
   *
   * @param productId
   */
  void requestProduct(int productId);
  /**
   * @brief
   *
   */
  void requestServerConfigs();
  /**
   * @brief
   *
   */
  void requestLicenceStatus();

  /**
   * @brief
   *
   * @param package
   */
  void dataReturned(rotable::ComPackageDataReturn* package);
  /**
   * @brief
   *
   * @param package
   */
  void dataChanged(rotable::ComPackageDataChanged* package);

  /**
   * @brief
   *
   * @param path
   */
  void loadServerConfigs(const QString& path);
  /**
   * @brief
   *
   * @param status
   */
  void loadLicenceStatus(const QString& status);

  /* MainWindow object */
  MainWindow* _mainwindow;

  /* Config object */
  ConfigAdmin _config;

  /* TCP client for connection to the server */
  TcpClient _tcp_client;

  QString _username;
  QString _password; /**< TODO: describe */

  /* Whether the user clicked disconnect (Avoid notification in that case) */
  bool _disconnectRequested;

  /* Currently pending data requests */
  QMap<QString, rotable::ComPackageDataRequest*> _dataRequest;

  /* Images */
  rotable::ImageContainer* _images;

  /* Products and categories */
  rotable::ProductContainer* _products;

  rotable::ProductCategory* _selectedCategory;
  rotable::Product* _selectedProduct; /**< TODO: describe */

  ServerLogListener _serverLogListener; /**< TODO: describe */
}; // class Executor

//------------------------------------------------------------------------------

#endif // EXECUTOR_H
