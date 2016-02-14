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
    _accepted(false), _state("DISCONNECTED"), _stopping(false), _config(configFilePath)
{

//  Always work, not need
//    switch (error) {
//    case FileNotLoaded:
//      qCritical() << tr("FATAL: Could not load %1").arg(configFilePath);
//      exit(EXIT_FAILURE);
//      break;
//    case FileNotFound:
//      qCritical() << tr("FATAL: File not found: %1").arg(configFilePath);
//      exit(EXIT_FAILURE);
//      break;
//    case FileNoReadAccess:
//      qCritical() << tr("FATAL: No read access on %1").arg(configFilePath);
//      exit(EXIT_FAILURE);
//      break;
//    case FileNoWriteAccess:
//      qCritical() << tr("FATAL: No write access on %1").arg(configFilePath);
//      exit(EXIT_FAILURE);
//      break;
//    case FileParseError:
//      qCritical() << tr("FATAL: Error parsing %1").arg(configFilePath);
//      exit(EXIT_FAILURE);
//      break;
//    default:
//      // everything is fine :)
//      break;
//    }

    _products = new ProductContainer();
    //set container for productlist(connect sigals-slots, etc.)
    _productsList.setContainer(_products);

    connect(&_tcp, SIGNAL(connected()),
            this, SLOT(connected()));
    connect(&_tcp, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
    connect(&_tcp, SIGNAL(packageReceived(ComPackage*)),
            this, SLOT(packageReceived(ComPackage*)));
    connect(&_reconnectTimer, SIGNAL(timeout()),
            this, SLOT(reconnect()));

    connect(&_tables, SIGNAL(updateOrderBoard(rotable::Table*)),
            &_board, SLOT(readOrderFromTable(rotable::Table*)));

    connect(&_board, &rotable::OrderBoard::unLoadTable,
            &_tables, &rotable::TableModel::unLoadTable);

    connect(&_needBoard, &rotable::NeedBoard::unsetWaiterNeed,
            this, &rotable::Waiter_Client::tableNeedWaiterChanged);
}


Waiter_Client::~Waiter_Client()
{
    _dataRequest.clear();     //Clear list
   // _stopping=true;

    delete _products;
}


//------------------------------------------------------------------------------

bool Waiter_Client::startup()
{
  reconnect();
  return true;
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
      requestTableList();
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
      //rejected(static_cast<ComPackageReject*>(package));
    } break;
//    case ComPackage::WaiterNeed:
//    {
//        ComPackageWaiterNeed *p = static_cast<ComPackageWaiterNeed*>(package);
//        _tables.updateWaiterIsNeed(p->need(), p->tableId());
//    } break;
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
    ComPackageDataRequest* request = new ComPackageDataRequest();
    request->setDataCategory(ComPackage::RequestTableIds);

    if (!_tcp.send(*request)) {
      qCritical() << tr("Could not send request!");
    } else {
      _dataRequest[request->id()] = request;
    }
}

//------------------------------------------------------------------------------

void Waiter_Client::sendOrders()
{
    //ToDo: Add code here
    Table *table = dynamic_cast<Table*>(QObject::sender());
    if(!table)
        return;
    QMap<int, QJsonValue> *list = table->getOrderJSON();
    QMap<int, QJsonValue>::const_iterator it = list->cbegin();
    for(; it!=list->cend(); ++it)
    {
        rotable::ComPackageDataSet package;
        package.setDataCategory(ComPackage::SetOrder);
        package.setData(it.value());
        package.setDataName(QString("%1").arg(it.key()));
        _tcp.send(package);
    }


}

//------------------------------------------------------------------------------

void Waiter_Client::tableNeedWaiterChanged(int id)
{
    // Prepare package
    rotable::ComPackageWaiterNeed* package = new ComPackageWaiterNeed();
    package->setNeed(false);        //Set state
    package->setTableId(id);        //Server set id for us
    if (!_tcp.send(*package))
      qCritical() << tr("Could not send package!");
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
      //TODO: create property table

      //Load data about order
      QJsonArray arr = package->data().toArray();
      foreach(QJsonValue value, arr){
          int tableId = value.toInt();
          requestTable(tableId);
      }
    } break;

    case ComPackage::RequestTable:
    {
      //Load data about order
      Table *table = Table::fromJSON(package->data());    
      if(_tables.addTable(table))
      {
          connect(table, &rotable::Table::sendOrders, this, &Waiter_Client::sendOrders);
          connect(table, &rotable::Table::waiterIsNeededChanged, &_needBoard, &rotable::NeedBoard::tableNeedChanged);
          requestOrderOnTable(table->id());
          emit table->waiterIsNeededChanged();
      }
      else
          delete table;

    } break;

    case ComPackage::RequestOrderOnTable:
    {
        QJsonArray arr = package->data().toArray();
        //If array is empty it's no need add orders to table
        if(arr.count() == 0)
            break;
        //Get tableId form first order
        int tableId = Order::fromJSON(arr[0])->clientId();
        //For each order
        foreach(QJsonValue value, arr){
            //Convert JSON to order
            Order *order = Order::fromJSON(value);
            //Add order to table
            _tables.updateOrder(tableId, order);
        }
    } break;
    //When someone change order
    case ComPackage::RequestOrder:
    {
        //Get order from json
        Order *order = Order::fromJSON(package->data());
        //Update order on table
        _tables.updateOrder(order->clientId(), order);
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

void Waiter_Client::requestOrderOnTable(int tableId)
{
    ComPackageDataRequest* request = new ComPackageDataRequest();
    request->setDataCategory(ComPackage::RequestOrderOnTable);
    request->setDataName(QString("%1").arg(tableId));

    if (!_tcp.send(*request)) {
      qCritical() << tr("Could not send request!");
    } else {
      _dataRequest[request->id()] = request;
    }
}

//------------------------------------------------------------------------------

void Waiter_Client::requestOrder(int orderId)
{
    ComPackageDataRequest* request = new ComPackageDataRequest();
    request->setDataCategory(ComPackage::RequestOrder);
    request->setDataName(QString("%1").arg(orderId));

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
       qCritical() << "reqest product :" << productId;
      if (!ok) {
        qCritical() << tr("Could not convert product id '%1' to int!")
                       .arg(package->dataName());
      } else {
        requestProduct(productId);
      }
    } break;
    case ComPackage::RequestTableIds:
    {
       requestTableList();
    } break;
    case ComPackage::RequestOrderIds:
    {
        bool ok;
        int tableId = package->dataName().toInt(&ok);
        if (!ok) {
          qCritical() << tr("Could not convert product id '%1' to int!")
                         .arg(package->dataName());
        } else {
          requestOrderOnTable(tableId);
        }
    } break;
    case ComPackage::RequestTable:
    {
        bool ok;
        int tableId = package->dataName().toInt(&ok);
        if (!ok) {
          qCritical() << tr("Could not convert table id '%1' to int!")
                         .arg(package->dataName());
        } else {
          requestTable(tableId);
        }
    } break;

    case ComPackage::RequestOrder:
    {
        bool ok;
        int orderId = package->dataName().toInt(&ok);
        if (!ok) {
          qCritical() << tr("Could not convert product id '%1' to int!")
                         .arg(package->dataName());
        } else {
          requestOrder(orderId);
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

void Waiter_Client::requestTable(int tableId)
{
    ComPackageDataRequest* request = new ComPackageDataRequest();
    request->setDataCategory(ComPackage::RequestTable);
    request->setDataName(QString("%1").arg(tableId));

    if (!_tcp.send(*request)) {
      qCritical() << tr("Could not send request!");
    } else {
      _dataRequest[request->id()] = request;
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
