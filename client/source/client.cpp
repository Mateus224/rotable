#include "private/precomp.h"

#include "client.h"
#include "compackage.h"
#include "utils.h"
#include "settings.h"
#include "categorylistmodel.h"
#include "productlistmodel.h"
#include "productcontainer.h"
#include "imageprovider.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------


Client::Client(const QString &configFilePath, QObject *parent)
  : QObject(parent),
    _accepted(false), _state("DISCONNECTED"), _stopping(false),
    _currentCategoryId(-1), _productListModel(0), _imageProvider(0)
{
  ConfigError error = _config.load(configFilePath);

  switch (error) {
  case FileNotLoaded:
    qCritical() << tr("FATAL: Could not load %1").arg(configFilePath);
    exit(EXIT_FAILURE);
    break;
  case FileNotFound:
    qCritical() << tr("FATAL: File not found: %1").arg(configFilePath);
    exit(EXIT_FAILURE);
    break;
  case FileNoReadAccess:
    qCritical() << tr("FATAL: No read access on %1").arg(configFilePath);
    exit(EXIT_FAILURE);
    break;
  case FileNoWriteAccess:
    qCritical() << tr("FATAL: No write access on %1").arg(configFilePath);
    exit(EXIT_FAILURE);
    break;
  case FileParseError:
    qCritical() << tr("FATAL: Error parsing %1").arg(configFilePath);
    exit(EXIT_FAILURE);
    break;
  default:
    // everything is fine :)
    break;
  }

  _products = new ProductContainer(this);

  connect(&_tcp, SIGNAL(connected()),
          this, SLOT(connected()));
  connect(&_tcp, SIGNAL(disconnected()),
          this, SLOT(disconnected()));
  connect(&_tcp, SIGNAL(packageReceived(ComPackage*)),
          this, SLOT(packageReceived(ComPackage*)));
  connect(&_reconnectTimer, SIGNAL(timeout()),
          this, SLOT(reconnect()));
  connect(&_sensors, SIGNAL(rotationChanged()),
          this, SIGNAL(rotationChanged()));
  connect(&_sensors, SIGNAL(contactChanged()),
          this, SIGNAL(contactChanged()));
}

//------------------------------------------------------------------------------

Client::~Client()
{
  _stopping = true;
}

//------------------------------------------------------------------------------

bool Client::startup()
{
  reconnect();
  return true;
}

//------------------------------------------------------------------------------

QAbstractListModel *Client::categoryListModel()
{
  return new CategoryListModel(this, _products);
}

//------------------------------------------------------------------------------

QAbstractListModel *Client::productListModel()
{
  if (0 == _productListModel) {
    _productListModel = new ProductListModel(this, _products);
  }

  return _productListModel;
}

//------------------------------------------------------------------------------

QString Client::currentCategoryName() const
{
  if (_currentCategoryId != -1) {
    ProductCategory* category = _products->category(_currentCategoryId);
    if (category) {
      return category->name();
    }
  }
  return QString();
}

//------------------------------------------------------------------------------

void Client::connected()
{
  qDebug() << tr("Connection established");

  ComPackageConnectionRequest request;
  request.setClientName(_config.clientName());
  if (!_tcp.send(request)) {
    qCritical() << tr("FATAL: Could not send connection request package!");
    exit(EXIT_FAILURE);
  }
}

//------------------------------------------------------------------------------

void Client::disconnected()
{
  setState("DISCONNECTED");

  if (!_stopping) {
    // Todo: do not reconnect if we want to close the app
    qDebug() << tr("Connection lost... trying to reconnect");

    _reconnectTimer.setSingleShot(true);
    _reconnectTimer.setInterval(500);
    _reconnectTimer.start();
  }
}

//------------------------------------------------------------------------------

void Client::packageReceived(ComPackage *package)
{
  if (package) {
    switch (package->type()) {
    case ComPackage::ConnectionRequest:
    {
      qCritical() << tr("ERROR: Received ConnectionRequest package!");
    } break;

    case ComPackage::ConnectionAccept:
    {
      qDebug() << tr("Client accepted by server.");
      _accepted = true;
      setState("SCREENSAVER");
      requestCategoryIds();
    } break;

    case ComPackage::DataRequest:
    {
      qCritical() << tr("ERROR: Received DataRequest package!");
    } break;

    case ComPackage::DataReturn:
    {
      dataReturned(static_cast<ComPackageDataReturn*>(package));
    } break;

    case ComPackage::DataChanged:
    {
      dataChanged(static_cast<ComPackageDataChanged*>(package));
    } break;

    case ComPackage::DataSet:
    {
      qCritical() << tr("ERROR: Received DataSet package!");
    } break;

    case ComPackage::Reject:
    {
      qDebug() << tr("WARNING: Package has been rejected!");
      rejected(static_cast<ComPackageReject*>(package));
    } break;

    default:
    {
      qDebug() << tr("WARNING: Received unknown package!");
    } break;
    }
  }
}

//------------------------------------------------------------------------------

void Client::rejected(ComPackageReject *rej)
{
  if (_dataRequest.contains(rej->originId())) {
    _dataRequest.remove(rej->originId());
  }
}

//------------------------------------------------------------------------------

void Client::setState(const QString &state)
{
  _state = state;
  emit stateChanged();
}

//------------------------------------------------------------------------------

void Client::setCurrentCategoryId(int id)
{
  if (id != _currentCategoryId || _state != "PRODUCTSCREEN") {
    _currentCategoryId = id;
    emit currentCategoryIdChanged();

    if (_productListModel) {
      _productListModel->setCategoryId(id);
    }

    if (_state != "PRODUCTSCREEN") {
      setState("PRODUCTSCREEN");
    }
  }
}

//------------------------------------------------------------------------------

void Client::reconnect()
{
  _tcp.startConnection(_config.serverAddress(), _config.port());
}

//------------------------------------------------------------------------------

void Client::requestCategoryIds()
{
  ComPackageDataRequest* request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestCategoryIds);

  if (!_tcp.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Client::requestProductIds(int categoryId)
{
  ComPackageDataRequest* request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestProductIds);
  request->setDataName(QString("%1").arg(categoryId));

  if (!_tcp.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Client::requestCategory(int categoryId)
{
  ComPackageDataRequest* request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestCategory);
  request->setDataName(QString("%1").arg(categoryId));

  if (!_tcp.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Client::requestProduct(int productId)
{
  ComPackageDataRequest* request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestProduct);
  request->setDataName(QString("%1").arg(productId));

  if (!_tcp.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

QString Client::requestImage(const QString& name)
{
  while (!_accepted) {
    delay(100);
  }

  ComPackageDataRequest* request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestImage);
  request->setDataName(name);
  if (!_tcp.send(*request)) {
    qCritical() << tr("Could not request image %1").arg(name);
  } else {
    _dataRequest[request->id()] = request;
  }

  return request->id();
}

//------------------------------------------------------------------------------

void Client::dataReturned(ComPackageDataReturn *package)
{
  if (package) {
    switch (package->dataCategory())
    {
    case ComPackage::RequestImage:
    {
      if (_imageProvider) {
        QByteArray ba = QByteArray::fromBase64(package->data().toString().toLocal8Bit(),
                                               QByteArray::Base64UrlEncoding);

        QImage img;
        if (!img.loadFromData(ba, ROTABLE_IMAGE_COMPRESSION)) {
          qCritical() << tr("ERROR: Could not create image from data the server has sent!");
        }

        _imageProvider->imageReceived(package->dataName(), img);
      } else {
        qDebug() << tr("Received image from server but has no image provider defined!");
      }
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
      _products->updateCategory(category);
    } break;

    case ComPackage::RequestProduct:
    {
      Product* product = Product::fromJSON(package->data());
      _products->updateProduct(product);
    } break;

    default:
    {
      qCritical() << tr("Unknown data package returned");
    } break;

    }
  }

  if (_dataRequest.contains(package->originId())) {
    _dataRequest.remove(package->originId());
  }
}

//------------------------------------------------------------------------------

void Client::dataChanged(rotable::ComPackageDataChanged *package)
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
