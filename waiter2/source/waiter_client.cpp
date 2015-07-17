#include "waiter_client.h"
#include "private/precomp.h"
#include "compackage.h"
#include "utils.h"
//#include "settings.h"
//#include "categorylistmodel.h"
//#include "productlistmodel.h"
#include "productcontainer.h"


//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------




Waiter_Client::Waiter_Client(const QString &configFilePath, QObject *parent)
  : QObject(parent),
    _accepted(false), _state("DISCONNECTED"), _stopping(false)
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
    _products = new ProductContainer();
    _productOrder = new ProductOrder(*_products);

    connect(&_tcp, SIGNAL(connected()),
            this, SLOT(connected()));
    connect(&_tcp, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
    connect(&_tcp, SIGNAL(packageReceived(ComPackage*)),
            this, SLOT(packageReceived(ComPackage*)));
    connect(&_reconnectTimer, SIGNAL(timeout()),
            this, SLOT(reconnect()));

}


Waiter_Client::~Waiter_Client()
{
   // _stopping=true;
}


//------------------------------------------------------------------------------

bool Waiter_Client::startup()
{
  reconnect();
  return true;
}

//------------------------------------------------------------------------------

QAbstractListModel *Waiter_Client::productOrderListModel()
{
  if (0 == _productOrderListModel) {
    _productOrderListModel = new ProductOrderListModel(NULL, NULL);
  }

  return _productOrderListModel;
}

//------------------------------------------------------------------------------

void Waiter_Client::reconnect()
{
  _tcp.startConnection(_config.serverAddress(), _config.port());
}

//------------------------------------------------------------------------------

void Waiter_Client::connected()
{
  qDebug() << tr("Connection established");

  ComPackageConnectionRequest request;
  request.setClientType(rotable::ComPackage::WaiterAccount);
  //Add login window
  request.setClientName("TestWaiter");
  request.setClientPass("TestWaiter");
  if (!_tcp.send(request)) {
    qCritical() << tr("FATAL: Could not send connection request package!");
    exit(EXIT_FAILURE);
  }

}

//------------------------------------------------------------------------------

void Waiter_Client::disconnected()
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

void Waiter_Client::packageReceived(ComPackage *package)
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
      requestTableList();
      //requestCategoryIds();
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
      //rejected(static_cast<ComPackageReject*>(package));
    } break;

    default:
    {
      qDebug() << tr("WARNING: Received unknown package!");
    } break;
    }
  }
}

//------------------------------------------------------------------------------

void Waiter_Client::rejected(ComPackageReject *rej)
{
  if (_dataRequest.contains(rej->originId())) {
    _dataRequest.remove(rej->originId());
  }
}

//------------------------------------------------------------------------------

void Waiter_Client::setState(const QString &state)
{
  _state = state;
  //emit stateChanged();
}

//------------------------------------------------------------------------------

void Waiter_Client::requestTableList()
{
    ComPackageDataRequest package;
    package.setDataCategory(ComPackage::RequestTableIds);
    _tcp.send(package);
}

//------------------------------------------------------------------------------

void Waiter_Client::dataReturned(ComPackageDataReturn *package)
{
  if (package) {
    switch (package->dataCategory())
    {
    case ComPackage::RequestImage:

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

    case ComPackage::RequestTableIds:
    {
      //TODO: add code to implement that
      // Temporary for check
      qDebug() << "Request Table: " << endl << package->data();
    } break;

    default:
    {
      qCritical() << tr("Unknown data package returned");
    } break;

    }
  }
}

//------------------------------------------------------------------------------

void Waiter_Client::requestCategory(int categoryId)
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

void Waiter_Client::requestProduct(int productId)
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

void Waiter_Client::requestProductIds(int categoryId)
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

void Waiter_Client::dataChanged(rotable::ComPackageDataChanged *package)
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

//------------------------------------------------------------------------------

void Waiter_Client::requestCategoryIds()
{
  ComPackageDataRequest* request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestCategoryIds);

  if (!_tcp.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}
