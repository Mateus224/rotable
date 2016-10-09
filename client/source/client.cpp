#include "private/precomp.h"
#include "client.h"
#include "compackage.h"
#include "utils.h"
#include "settings.h"
#include "categorylistmodel.h"
#include "productlistmodel.h"
#include "productcontainer.h"
#include "imageprovider.h"
#include "productorder.h"
#include <QtNetwork/QNetworkInterface>

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------


Client::Client(const QString &configFilePath, QObject *parent)
  : QObject(parent),
    _config(configFilePath, parent), _accepted(false), _state("DISCONNECTED"), _stopping(false),
    _currentCategoryId(-1),  _productListModel(0), _imageProvider(0)
{
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
  connect(&_sensors, SIGNAL(rotationChanged()),
          this, SIGNAL(rotationChanged()));
  connect(&_sensors, SIGNAL(contactChanged()),
          this, SIGNAL(contactChanged()));

   //_device=device;
   //_sensors._device=device;
  //MessageConnector
  connect(this, &Client::reciveMessagePackage, &_connector, &MessageConnector::reciveMessagePackage);
  //Binding for Message type
  _connector.addBindMethod(rotable::Message::OrderMessageType, &Client::orderSendSuccesfull, this);
  _connector.addBindMethod(rotable::Message::NeedWaiterMessageType, &Client::needWaiterStatus, this);
  _connector.addBindMethod(rotable::Message::QueueMessageType, &Client::orderQueue, this);

  // Connect send package from callWaiter by Client
  connect(&_callWaiter, &rotable::CallWaiter::sendCallWaiter,
          this, &Client::sendPackage);
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
    _productListModel = new ProductListModel(NULL, _products);
  }

  return _productListModel;
}

//------------------------------------------------------------------------------

//QAbstractListModel *Client::productOrderListModel()
//{
//  if (0 == _productorderlistmodel) {
//    _productorderlistmodel = new ProductOrderListModel(NULL, _productOrder);
//  }

//  return _productorderlistmodel;
//}
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
  request.setClientType(rotable::ComPackage::TableAccount);
  request.setClientPass(_config.macAdress());

  if (!_tcp.send(request)) {
    qCritical() << tr("FATAL: Could not send connection request package!");
    exit(EXIT_FAILURE);
  }
}

//------------------------------------------------------------------------------

void Client::disconnected()
{
  setState("DISCONNECTED");
  _accepted = false;

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

    case rotable::ComPackage::WaiterNeed:
    {
      ComPackageWaiterNeed *need = static_cast<ComPackageWaiterNeed*>(package);
      _callWaiter.setWaiterNeed(need->need());
    } break;

    case rotable::ComPackage::Message:
    {
        ComPackageMessage *msg = static_cast<ComPackageMessage*>(package);
        emit reciveMessagePackage(msg);
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

  if(_accepted == false)
  {
    QTimer *timer = new QTimer();
    timer->setSingleShot(true);
    timer->setInterval(5000);
    connect(timer, &QTimer::timeout, this, &Client::connected);
    connect(timer, &QTimer::timeout, timer, &QTimer::deleteLater);
    timer->start();
  }
}

//------------------------------------------------------------------------------

int Client::screenRotation()
{
    if(state() != "GAMEPAGE")
    {
        qDebug()<<_sensors.screenRotation();
        _lastRotation=_sensors.screenRotation();
        return _sensors.screenRotation();
    }
    else
        qDebug()<<_lastRotation<<" not "<<state();
        return _lastRotation;
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
    qDebug()<<"_productListModel:"<<_productListModel;
    if(id==-1)
    {
        if (_state != "CALLWAITERPAGE") {
          setState("CALLWAITERPAGE");
        }
    }
    else if(id==-2) //TODO implement games and waitor
    {
        if (_state != "GAMEPAGE") {
          setState("GAMEPAGE");
        }
    }

    else {
         if (_productListModel) {
            setState("PRODUCTSCREEN");
            _productListModel->setCategoryId(id);
        }
    }
  }
}

//------------------------------------------------------------------------------

void Client::sendOrder()
{
    ComPackageDataSet data = _productOrder->prepareOrderToSend();
    //Block sending order withwout orderitem
    if(data.dataCategory() != -1)
        _tcp.send(data);
    else
        invalidOrder();
}

//------------------------------------------------------------------------------

void Client::sendPackage(ComPackage *package)
{
    if (!_tcp.send(*package))
        qCritical() << tr("Could not send package!");
}

//------------------------------------------------------------------------------

void Client::orderSendSuccesfull(Message *msg)
{
    OrderMessage *message = static_cast<OrderMessage*>(msg);
    if(message->getError() == 0)
        this->setState("SENDACCEPT");
    else
        invalidOrder();
    delete message;
}

//------------------------------------------------------------------------------

void Client::invalidOrder()
{
    _productOrder->b_acceptOrder();
}
//------------------------------------------------------------------------------

void Client::orderQueue(Message *msg)
{
    QueueMessage *message = static_cast<QueueMessage*>(msg);
    if(!message->map().empty())
    {
        int iOrderQueue=message->map().firstKey();
        _queue.setqueueOrder(iOrderQueue);
        _queue.queueOrderChanged();
    }
    else{
        _queue.setqueueOrder(0);
        _queue.queueOrderChanged();
    }
    delete message;

}

//------------------------------------------------------------------------------

void Client::needWaiterStatus(Message *msg)
{
    NeedWaiterMessage *message = static_cast<NeedWaiterMessage*>(msg);

    if(!message->acceptStatusChange())
        _callWaiter.changeWaiterNeed();
    _callWaiter.setPropertyState();
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
      QList<int> newCategoryIds;
      foreach (QJsonValue val, arr) {
        int id = val.toInt();
        newCategoryIds.append(id);
        requestCategory(id);
      }
      foreach (int categoryId, _products->categoryIds()) {
        if(!newCategoryIds.contains(categoryId))
        {
            _products->removeCategory(categoryId);
            if(categoryId == _currentCategoryId)
                setState("STARTSCREEN");

        }
      }
    } break;

    case ComPackage::RequestProductIds:
    {
      QList<int> newProductIds;
      QJsonArray arr = package->data().toArray();
      foreach (QJsonValue val, arr) {
        int id = val.toInt();
        newProductIds.append(id);
        requestProduct(id);
      }

      int categoryId  = package->dataName().toInt();

      foreach (int productId, _products->productIds(categoryId)) {
        if(!newProductIds.contains(productId))
        {
            _products->removeProduct(productId);
            if(_productOrder->productId() == productId)
            {
                _productOrder->setproductid(-1);
            }

        }
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
//      _products->clear();
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
