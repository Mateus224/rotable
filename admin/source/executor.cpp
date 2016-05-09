#include "private/precomp.h"

#include "executor.h"
#include "connecttoserverdialog.h"
#include "addproductdialog.h"
#include "addproductcategory.h"
#include "addnewlicence.h"
#include "mainwindow.h"
#include "utils.h"
#include "productcategory.h"
#include "productcontainer.h"

#include <QBuffer>

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

Executor::Executor(MainWindow* mainwindow, const QString& configFilePath,
                   QObject *parent)
  : QObject(parent), _mainwindow(mainwindow), _disconnectRequested(false),
    _images(0), _products(0), _config(configFilePath)
{
  connect(&_tcp_client, SIGNAL(connected()), this, SLOT(onConnectionEstablished()));
  connect(&_tcp_client, SIGNAL(disconnected()), this, SLOT(onConnectionLost()));
  connect(&_tcp_client, SIGNAL(disconnected()), this, SIGNAL(connectionLost()));

  connect(&_tcp_client, SIGNAL(packageReceived(rotable::ComPackage*)),
          this, SLOT(onPackageReceived(rotable::ComPackage*)));
  connect(&_tcp_client, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SLOT(onClientError(QAbstractSocket::SocketError)));
  connect(&_serverLogListener, SIGNAL(connectionEstablished()),
          this, SIGNAL(serverLogConnectionEstablished()));
  connect(&_serverLogListener, SIGNAL(disconnected()),
          this, SIGNAL(serverLogConnectionLost()));
  connect(&_serverLogListener, SIGNAL(log(rotable::LogManager::LogMessage)),
          this, SIGNAL(serverLog(rotable::LogManager::LogMessage)));

//  if (NoError != _config.load(configFilePath)) {
//    qDebug() << tr("Could not load %1: %2").arg(configFilePath).arg(_config.errorStr());
//  }
}

//------------------------------------------------------------------------------

void Executor::setImageContainer(ImageContainer *images)
{
  _images = images;
}

//------------------------------------------------------------------------------

void Executor::setProductContainer(ProductContainer *products)
{
  _products = products;
}

//------------------------------------------------------------------------------

void Executor::onConnectToServer()
{
  ConnectToServerDialog dlg(_mainwindow);

  dlg.setServerAddress(_config.serverAddress());
  dlg.setServerPort(_config.serverPort());
  dlg.setUsername(_config.adminName());

  if (dlg.exec() == QDialog::Accepted) {
    emit statusMessage(tr("Connecting to %1:%2")
                       .arg(dlg.serverAddress())
                       .arg(dlg.serverPort()));

    _config.setServerAddress(dlg.serverAddress());
    _config.setServerPort(dlg.serverPort());
    _config.setServerAdminName(dlg.username());

    _tcp_client.startConnection(dlg.serverAddress(), dlg.serverPort());

    _username = dlg.username();
    _password = dlg.password();
  }
}

//------------------------------------------------------------------------------

void Executor::onDisconnectFromServer()
{
  _disconnectRequested = true;
  _tcp_client.closeConnection();

  emit statusMessage(tr("Disconnected"));
}

//------------------------------------------------------------------------------

void Executor::onAddProductCategory()
{
  AddProductCategory dlg(_images, _mainwindow);
  dlg.setProductContainer(_products);

  if (dlg.exec() == QDialog::Accepted) {
    ProductCategory pc;
    pc.setName(dlg.categoryName());
    pc.setIcon(dlg.iconName());
    pc.setId(-1); // mark as new category

    ComPackageDataSet set;
    set.setDataCategory(ComPackage::SetCategory);
    set.setData(pc.toJSON());

    if (!_tcp_client.send(set)) {
      qCritical() << tr("FATAL: Could not send data set package!");

      QMessageBox msgBox;
      msgBox.setText("Network I/O-Error!");
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.exec();
    }
  }
}

//------------------------------------------------------------------------------

void Executor::onUpdateCategory(ProductCategory *category)
{
  if (category) {
    ComPackageDataSet set;
    set.setDataCategory(ComPackage::SetCategory);
    set.setData(category->toJSON());

    if (!_tcp_client.send(set)) {
      qCritical() << tr("FATAL: Could not send data set package!");
    }
  }
}

//------------------------------------------------------------------------------

void Executor::onAddProduct()
{
  AddProductDialog dlg(_images, _mainwindow);
  dlg.setProductContainer(_products);
  if (_selectedCategory) {
    dlg.setCategory(_selectedCategory->id());
  }

  if (dlg.exec() == QDialog::Accepted) {
    Product p;
    p.setName(dlg.productName());
    p.setIcon(dlg.iconName());
    p.setId(-1); // mark as new category
    p.setInfo(dlg.productInfo());
    p.setPrice(dlg.productPrice());
    p.setCategoryId(dlg.categoryId());
    p.setAmount(dlg.productAmount());

    ComPackageDataSet set;
    set.setDataCategory(ComPackage::SetProduct);
    set.setData(p.toJSON());

    if (!_tcp_client.send(set)) {
      qCritical() << tr("FATAL: Could not send data set package!");

      QMessageBox msgBox;
      msgBox.setText("Network I/O-Error!");
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.exec();
    }
  }
}

//------------------------------------------------------------------------------

void Executor::onUpdateProduct(Product *product)
{
  if (product) {
    ComPackageDataSet set;
    set.setDataCategory(ComPackage::SetProduct);
    set.setData(product->toJSON());

    if (!_tcp_client.send(set)) {
      qCritical() << tr("FATAL: Could not send data set package!");
    }
  }
}

//------------------------------------------------------------------------------

void Executor::onResetDatabase()
{
  QMessageBox msgBox;
  msgBox.setText(tr("This operation will clear your entire database. Are you sure you want to continue?"));
  msgBox.setInformativeText("Clear entire database?");
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.setDefaultButton(QMessageBox::No);
  msgBox.setIcon(QMessageBox::Warning);
  if (msgBox.exec() == QMessageBox::Yes) {
    ComPackageCommand com;
    com.setCommandType(ComPackage::ResetDatabase);

    if (!_tcp_client.send(com)) {
      qCritical() << tr("FATAL: Could not send command package!");

      QMessageBox msgBox;
      msgBox.setText("Network I/O-Error!");
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.exec();
    }
  }
}

//------------------------------------------------------------------------------

void Executor::onExportDatabase()
{

}

//------------------------------------------------------------------------------

void Executor::onImportDatabase()
{

}

//------------------------------------------------------------------------------

void Executor::onRemoveCurrentEntry()
{
  if (_selectedCategory) {
    ComPackageCommand com;

    if (_selectedProduct) {
      //_products->removeProduct(_selectedProduct);
      //_selectedProduct = 0;

      com.setData(_selectedProduct->id());
      com.setCommandType(ComPackage::DeleteProduct);
    } else {
      //_products->removeCategory(_selectedCategory);
      //_selectedCategory = 0;

      com.setData(_selectedCategory->id());

      com.setCommandType(ComPackage::DeleteCategory);
    }

    if (!_tcp_client.send(com)) {
      qCritical() << tr("FATAL: Could not send data set package!");

      QMessageBox msgBox;
      msgBox.setText("Network I/O-Error!");
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.exec();
    }
  }
}

//------------------------------------------------------------------------------

void Executor::onRenameCurrentEntry()
{

}

//------------------------------------------------------------------------------

void Executor::onCategorySelectionChanged(int id)
{
  if (id == -1) {
    _selectedCategory = 0;
    _selectedProduct = 0;
  } else {
    _selectedCategory = _products->category(id);
    _selectedProduct = 0;
    Q_ASSERT(_selectedCategory);
  }
}

//------------------------------------------------------------------------------

void Executor::onProductSelectionChanged(int id)
{
  if (id == -1) {
    _selectedProduct = 0;
  } else {
    _selectedProduct = _products->product(id);
    Q_ASSERT(_selectedProduct);
  }
}

//------------------------------------------------------------------------------

void Executor::onExportStatistic()
{
  _mainwindow->exportPdf();
}

//------------------------------------------------------------------------------

void Executor::onClearDebugServerLog()
{
  _mainwindow->clearDebugServerLog();
}

//------------------------------------------------------------------------------

void Executor::onStartDebugServerListening()
{
  _serverLogListener.startConnection("127.0.0.1", 5001);
}

//------------------------------------------------------------------------------

void Executor::onStopDebugServerListening()
{
    _serverLogListener.stopConnection();
}

//------------------------------------------------------------------------------

void Executor::onAddLicence()
{
    AddNewLicence dlg(_mainwindow);

    if (dlg.exec() == QDialog::Accepted) {
    }
//    QFile file;
//    QStringList fileList;
//    QJsonArray array;

//    foreach(QString fileName, fileList)
//    {
//        file.setFileName(fileName);

//        QByteArray ba;
//        QBuffer buffer(&ba);

//        ba = file.readAll();
//        QString base64 = ba.toBase64(QByteArray::Base64UrlEncoding);

//        array.append(QJsonValue(base64));
//    }
}

//------------------------------------------------------------------------------

void Executor::onClientError(QAbstractSocket::SocketError error)
{
  QMessageBox msgBox;
  msgBox.setText(QString("Network Error: %1").arg(SocketErrorToString(error)));
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.setIcon(QMessageBox::Critical);
  msgBox.exec();
}

//------------------------------------------------------------------------------

void Executor::onConnectionEstablished()
{
  ComPackageConnectionRequest request;
  request.setClientName(_username);
  request.setClientPass(_password);
  request.setClientType(rotable::ComPackage::AdminAccount);

  if (!_tcp_client.send(request)) {
    qCritical() << tr("FATAL: Could not send connection request package!");

    QMessageBox msgBox;
    msgBox.setText("Network I/O-Error!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
  }
}

//------------------------------------------------------------------------------

void Executor::onConnectionLost()
{
  if (!_mainwindow->isClosing() && !_disconnectRequested) {
    QMessageBox msgBox;
    msgBox.setText("Connection to server lost.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIconPixmap(QPixmap(QStringLiteral(":/rotable/network-connect.png")).scaledToHeight(32));
    msgBox.exec();
  }

  _products->clear();
  _disconnectRequested = false;
}

//------------------------------------------------------------------------------

void Executor::onPackageReceived(ComPackage *package)
{
  if (package) {
    switch (package->type()) {
    case ComPackage::ConnectionRequest:
      qCritical() << tr("ERROR: Received ConnectionRequest package!");
      break;

    case ComPackage::ConnectionAccept:
      emit connectionEstablished();
      emit statusMessage(tr("Connected"));
      requestCategoryIds();
      requestServerConfigs();
      requestLicenceStatus();
      break;

    case ComPackage::DataRequest:
      qCritical() << tr("ERROR: Received DataRequest package!");
      break;

    case ComPackage::DataReturn:
      dataReturned(static_cast<ComPackageDataReturn*>(package));
      break;

    case ComPackage::DataChanged:
      dataChanged(static_cast<ComPackageDataChanged*>(package));
      break;

    case ComPackage::DataSet:
      qCritical() << tr("ERROR: Received DataSet package!");
      break;

    case ComPackage::Reject:
    {
      _dataRequest.remove(static_cast<ComPackageReject*>(package)->originId());

      qDebug() << tr("WARNING: Package has been rejected!");

      QMessageBox msgBox;
      msgBox.setText("Request rejected by server.");
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.setIcon(QMessageBox::Warning);
      msgBox.exec();
    } break;

    default:
      qDebug() << tr("WARNING: Received unknown package!");
      break;
    }
  }
}

//------------------------------------------------------------------------------

void Executor::requestCategoryIds()
{
  ComPackageDataRequest* request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestCategoryIds);

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestProductIds(int categoryId)
{
  ComPackageDataRequest* request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestProductIds);
  request->setDataName(QString("%1").arg(categoryId));

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestCategory(int categoryId)
{
  ComPackageDataRequest* request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestCategory);
  request->setDataName(QString("%1").arg(categoryId));

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestProduct(int productId)
{
  ComPackageDataRequest* request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestProduct);
  request->setDataName(QString("%1").arg(productId));

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestServerConfigs()
{
    ComPackageDataRequest* request = new ComPackageDataRequest();
    request->setDataCategory(ComPackage::RequestConfig);

    if (!_tcp_client.send(*request)) {
      qCritical() << tr("Could not send request!");
    } else {
      _dataRequest[request->id()] = request;
    }
}

//------------------------------------------------------------------------------

void Executor::requestLicenceStatus()
{
    ComPackageDataRequest* request = new ComPackageDataRequest();
    request->setDataCategory(ComPackage::RequestLicence);

    if (!_tcp_client.send(*request)) {
      qCritical() << tr("Could not send request!");
    } else {
      _dataRequest[request->id()] = request;
    }
}

//------------------------------------------------------------------------------

void Executor::dataReturned(ComPackageDataReturn *package)
{
  _dataRequest.remove(package->originId());

  switch (package->dataCategory()) {
  case ComPackage::RequestImage:
  {
    qCritical() << tr("The server request an imag from us!?!");
  } break;

  case ComPackage::RequestCategoryIds:
  {
    QJsonArray arr = package->data().toArray();
    foreach (QJsonValue val, arr) {
      int id = val.toInt();
      requestCategory(id);
    }
  } break;

  case ComPackage::RequestProductIds:
  {
    QJsonArray arr = package->data().toArray();
    foreach (QJsonValue val, arr) {
      int id = val.toInt();
      requestProduct(id);
    }
  } break;

  case ComPackage::RequestCategory:
  {
    ProductCategory* category = ProductCategory::fromJSON(package->data());
    requestProductIds(category->id());
    _products->addCategory(category);
  } break;

  case ComPackage::RequestProduct:
  {
    Product* product = Product::fromJSON(package->data());
    _products->addProduct(product);
  } break;

  case ComPackage::RequestConfig:
  {
    loadServerConfigs(package->data().toString());
  } break;
  case ComPackage::RequestLicence:
  {
    loadLicenceStatus(package->data().toString());
  } break;
  default:
  {
    qCritical() << tr("Unknown data package returned");
  } break;
  }
}

//------------------------------------------------------------------------------

void Executor::dataChanged(ComPackageDataChanged *package)
{
  if (package) {
    switch (package->dataCategory()) {
    case ComPackage::RequestImage:
    {
    } break;
    case ComPackage::RequestCategoryIds:
    {
      _products->clear();
      requestCategoryIds();
    } break;
    case ComPackage::RequestProductIds:
    {
      bool ok;
      int categoryId = package->dataName().toInt(&ok);
      if (!ok) {
        qCritical() << tr("Could not convert category id '%1' to int!")
                       .arg(package->dataName());
      } else {
        _products->clearProducts(categoryId);
        requestProductIds(categoryId);
      }
    } break;
    case ComPackage::RequestCategory:
    {
      bool ok;
      int categoryId = package->dataName().toInt(&ok);
      if (!ok) {
        qCritical() << tr("Could not convert category id '%1' to int!")
                       .arg(package->dataName());
      } else {
        requestCategory(categoryId);
      }
    } break;
    case ComPackage::RequestProduct:
    {
      bool ok;
      int productId = package->dataName().toInt(&ok);
      if (!ok) {
        qCritical() << tr("Could not convert product id '%1' to int!")
                       .arg(package->dataName());
      } else {
        requestProduct(productId);
      }
    } break;
    default:
    {
      qCritical() << tr("Unknown data changed category '%1' received!")
                     .arg(package->dataCategory());
    } break;
    }
  }
}

//------------------------------------------------------------------------------

void Executor::loadServerConfigs(const QString &path)
{
    emit onLicenceConfig("path");
}

//------------------------------------------------------------------------------

void Executor::loadLicenceStatus(const QString &status)
{
    emit onLicenceStatus(status);
}

//------------------------------------------------------------------------------
