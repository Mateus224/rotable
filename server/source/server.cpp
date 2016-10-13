#include "private/precomp.h"

#include "logmanager.h"
#include "message.h"
#include "productorder.h"
#include "server.h"
#include "settings.h"

#include <QFile>
#include <QStandardPaths>

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

Server::Server(const QString &configFilePath, QObject *parent)
  : QObject(parent), _config(configFilePath, this), _tcp(this), _db(this)
{
  connect(&_tcp, SIGNAL(clientConnected(client_t)),
          this, SLOT(clientConnected(client_t)));
  connect(&_tcp, SIGNAL(clientDisconnected(client_t,QString)),
          this, SLOT(clientDisconnected(client_t,QString)));
  connect(&_tcp, SIGNAL(packageReceived(client_t,ComPackage*)),
          this, SLOT(packageReceived(client_t,ComPackage*)));
  // if we add or update any config we parse them
  connect(&_db, &Database::parseConfig, this, &Server::config_parser);
  schedule = new Schedule();

  //  _licence = new Licence(_config.licence_path());

  //  connect(_licence, &rotable::Licence::getLastIncomeDate, &_db,
  //  &rotable::Database::getLastIncome);
}

//------------------------------------------------------------------------------

Server::~Server() {
  delete schedule;
  //    delete _licence;
}

//------------------------------------------------------------------------------

bool Server::startup() {
  // Now config is always create
  //  if (_config.error() != NoError) {
  //    qCritical() << tr("Config file error: %1").arg(_config.errorStr());
  //    return false;
  //  }

  _images.clear();

  if (!_db.startConnection(ROTABLE_DATABASE_CLIENT, _config.db_host(),
                           _config.db_name(), _config.db_user(),
                           _config.db_pass(), _config.db_prefix())) {
    qCritical() << tr("Could not connect with database server at %1")
                       .arg(_config.db_host());
    return false;
  } else {
    // Init empty database if none existing
    if (!_db.databaseExists()) {
      qDebug() << tr("Creating initial database...");
      if (!_db.createDatabase()) {
        qCritical() << tr("Could not create database!");
      }
    } else
      _db.update();
  }
  qDebug() << "test";

  if (!_tcp.start(_config.port())) {
    qCritical() << tr("FATAL: Could not start listening on port %1\n")
                       .arg(_config.port());
    return false;
  }

  foreach (const ConfigServer::Image& i, _config.images()) {
    if (!QFile(i.path).exists()) {
      qDebug() << tr("WARNING: Image %1 does not exist at %2!")
                  .arg(i.name, i.path);
    } else {
      Image img;
      img.path = i.path;
      if (!img.img.load(i.path)) {
        qDebug() << tr("WARNING: Could not load Image %1 at %2!")
                    .arg(i.name, i.path);
      } else {
        _images[i.name] = img;
        qDebug() << tr("Image %1 loaded.").arg(i.path);
      }
    }
  }

  load_configs();

  qDebug() << tr("Listening for incoming connections on port %1").arg(_config.port());

  return true;
}

//------------------------------------------------------------------------------

void Server::createDatabase() {
  if (!_db.createDatabase()) {
    qCritical() << tr("Could not create database!");
  }
}

//------------------------------------------------------------------------------

void Server::clientConnected(client_t client) {
  qDebug() << tr("Client connected: %1")
                  .arg(_tcp.clientSocket(client)->peerAddress().toString());
}

//------------------------------------------------------------------------------

void Server::packageReceived(client_t client, ComPackage *package) {
  switch (package->type()) {
  case ComPackage::ConnectionRequest: {
    ComPackageConnectionRequest *p =
        static_cast<ComPackageConnectionRequest *>(package);
    if (login(p, client)) {
      if (p->clientType() == rotable::ComPackage::TableAccount)
      {
        ;
      //          if(Q_UNLIKELY(!_licence->getLicence(_tcp.clientSocket(client))))
      //          {
      //              ComPackageReject reject(package->id());
      //              _tcp.send(client, reject);
      //              break;
      //          }
      }
      _tcp.setClientName(client, p->clientName());
      ComPackageConnectionAccept accept;
      _tcp.send(client, accept);
    } else {
      ComPackageReject reject(package->id());
      _tcp.send(client, reject);
    }
  } break;
  case ComPackage::ConnectionAccept: {
    qDebug() << tr(
        "Did not expect to receive ConnectionAccept package... rejecting");
    ComPackageReject reject(package->id());
    _tcp.send(client, reject);
  } break;
  case ComPackage::Message: {
    qDebug() << tr(
        "Did not expect to receive Message package... rejecting");
    ComPackageReject reject(package->id());
    _tcp.send(client, reject);
  } break;
  case ComPackage::DataRequest: {
    if (_tcp.isClientAccepted(client)) {
      ComPackageDataRequest *p = static_cast<ComPackageDataRequest *>(package);

      ComPackageDataReturn *ret = getData(p, client);
      if (ret) {
        _tcp.send(client, *ret);
      } else {
        ComPackageReject reject(package->id());
        _tcp.send(client, reject);
      }
    } else {
      qDebug() << tr("WARNING: Unallowed DataRequest from client \"%1\"")
                      .arg(_tcp.clientName(client));
      ComPackageReject reject(package->id());
      _tcp.send(client, reject);
    }
  } break;
  case ComPackage::DataReturn: {
    qDebug() << tr("Did not expect to receive DataReturn package... rejecting");
    ComPackageReject reject(package->id());
    _tcp.send(client, reject);
  } break;
  case ComPackage::DataChanged: {
    qDebug() << tr(
        "Did not expect to receive DataChanged package... rejecting");
    ComPackageReject reject(package->id());
    _tcp.send(client, reject);
  } break;
  case ComPackage::DataSet: {
    if (_tcp.isClientAccepted(client)) {
      ComPackageDataSet *p = static_cast<ComPackageDataSet *>(package);

      if (!setData(p, client)) {
        ComPackageReject reject(package->id());
        _tcp.send(client, reject);
      }

    } else {
      qDebug() << tr("WARNING: Unallowed DataSet from client \"%1\"")
                      .arg(_tcp.clientName(client));
      ComPackageReject reject(package->id());
      _tcp.send(client, reject);
    }
  } break;
  case ComPackage::Command: {
    if (_tcp.isClientAccepted(client)) {
      ComPackageCommand *p = static_cast<ComPackageCommand *>(package);

      if (!executeCommand(p)) {
        ComPackageReject reject(package->id());
        _tcp.send(client, reject);
      }
    } else {
      qDebug() << tr("WARNING: Unallowed Command from client \"%1\"")
                      .arg(_tcp.clientName(client));
      ComPackageReject reject(package->id());
      _tcp.send(client, reject);
    }
  } break;
  case ComPackage::WaiterNeed: {
    if (_tcp.isClientAccepted(client)) {

      ComPackageWaiterNeed *p = static_cast<ComPackageWaiterNeed *>(package);
      int id;
      bool updateTable = false;

      // Check account type
      if (_users[rotable::ComPackage::TableAccount].contains(client))
        id = _users[1][client];
      else if (_users[rotable::ComPackage::WaiterAccount].contains(client)) {
        id = p->tableId();
        updateTable = true;
      } else {
        qDebug() << tr("WARNING: Package send form unconnect devices ' \"%1\"")
                        .arg(_tcp.clientName(id));
        ComPackageReject reject(package->id());
        _tcp.send(client, reject);
      }

      if (!setWaiterNeed(p->need(), id)) {
        qDebug() << tr("WARNING: Can't set status for table' \"%1\"")
                        .arg(_tcp.clientName(id));
        ComPackageReject reject(package->id());
        _tcp.send(client, reject);

        NeedWaiterMessage msg;
        msg.unSuccess();
        _tcp.send(client, *(msg.toPackage()));

      } else {
        // Send information to waiter about table change
        ComPackageDataChanged dc;
        dc.setDataCategory(rotable::ComPackage::RequestTable);
        dc.setDataName(QString("%1").arg(id));
        _tcp.send(-1, dc);
        send_to_users(dc, rotable::ComPackage::WaiterAccount);

        if (updateTable) {
          ComPackageWaiterNeed *change = new ComPackageWaiterNeed();
          change->setNeed(p->need());
          change->setTableId(id);
          _tcp.send(_users[rotable::ComPackage::TableAccount].key(id), *change);
        }

        NeedWaiterMessage msg;
        // ToDo: change to position in queue
        msg.success(p->need() ? 0 : -1);
        _tcp.send(client, *(msg.toPackage()));
      }
    } else {
      qDebug() << tr("WARNING: Unallowed Command from client \"%1\"")
                      .arg(_tcp.clientName(client));
      ComPackageReject reject(package->id());
      _tcp.send(client, reject);
    }
  } break;     
  case ComPackage::File:
  {
      if (_tcp.isClientAccepted(client))
      {
          ComPackageSendFile* p=static_cast <ComPackageSendFile*>(package);
          if (!kindOfFileDestination(p)) {
            ComPackageReject reject(package->id());
            _tcp.send(client, reject);
          }

      }
      else{
          qDebug() << tr("WARNING: Unallowed Command from client \"%1\"")
                      .arg(_tcp.clientName(client));
          ComPackageReject reject(package->id());
          _tcp.send(client, reject);
    }
  case ComPackage::Reject: {
    qDebug() << tr("Did not expect to receive Reject package... doing nothing");
  } break;
  }
}

//------------------------------------------------------------------------------

void Server::clientDisconnected(client_t client, const QString &clientName) {
  qDebug() << tr("Client %1 disconnected").arg(clientName);

  // remove client from _users
  // we don't know in with QMap it is
  // so we remove element from all QMap

  if (_users[rotable::ComPackage::TableAccount].contains(client)) {
    _db.changeTableConnectStatus(
        _users[rotable::ComPackage::TableAccount].value(client), false);
    ComPackageDataChanged dc;
    dc.setDataCategory(ComPackage::RequestTable);
    dc.setDataName(QString::number(
        _users[rotable::ComPackage::TableAccount].value(client)));
    send_to_users(dc, ComPackage::WaiterAccount);
  }

  // Check if wneed remove element from waiter list
  if(_waiterList.contains(client)){
    delete _waiterList[client];
    _waiterList.remove(client);
  }

  for (int i = 0; i < 3; ++i)
    _users[i].remove(client);
}

//------------------------------------------------------------------------------

ComPackageDataReturn *Server::getData(ComPackageDataRequest *request,
                                      client_t client) {
  switch (request->dataCategory()) {
  case ComPackage::RequestImage: {
    if (_images.contains(request->dataName())) {
      const QImage &img = _images[request->dataName()].img;

      QByteArray ba;
      QBuffer buffer(&ba);
      img.save(&buffer, ROTABLE_IMAGE_COMPRESSION);

      QString base64 = ba.toBase64(QByteArray::Base64UrlEncoding);
      QJsonValue jsonVal(base64);

      return new ComPackageDataReturn(*request, jsonVal);
    } else {
      qDebug() << tr("ERROR: Requested image %1 is unknown!")
                      .arg(request->dataName());
    }
  } break;
  case ComPackage::RequestCategoryIds: {
    QList<int> ids;
    if (_db.categoryIds(ids)) {
      QJsonArray arr;
      foreach (int id, ids) { arr.append(id); }
      QJsonValue jsonVal(arr);

      return new ComPackageDataReturn(*request, jsonVal);
    } else {
      qCritical() << tr("Could not query product category ids!");
    }
  } break;
  case ComPackage::RequestProductIds: {
    bool ok;
    int categoryId = request->dataName().toInt(&ok);
    if (ok) {
      QList<int> ids;
      if (_db.productIds(ids, categoryId)) {
        QJsonArray arr;
        foreach (int id, ids) { arr.append(id); }
        QJsonValue jsonVal(arr);

        return new ComPackageDataReturn(*request, jsonVal);
      } else {
        qCritical() << tr("Could not query product ids for category %1!")
                           .arg(categoryId);
      }
    } else {
      qCritical() << tr("Could not convert category id '%1' to an integer!")
                         .arg(request->dataName());
    }
  } break;
  case ComPackage::RequestTableIds: {
    QList<int> ids;
    if (_db.clientIds(ids, rotable::ComPackage::TableAccount)) {
      QJsonArray arr;
      foreach (int id, ids)
        arr.append(id);
      QJsonValue jsonVal(arr);
      return new ComPackageDataReturn(*request, jsonVal);
    } else
      qCritical() << tr("Could not query users ids for account type %1!")
                         .arg(rotable::ComPackage::TableAccount);
  } break;
  case ComPackage::RequestTable: {
    bool ok;
    int tableId = request->dataName().toInt(&ok);
    if (ok) {
      Table *table = reinterpret_cast<Table *>(_db.client(tableId));
      if (table) {
        ComPackageDataReturn *ret =
            new ComPackageDataReturn(*request, table->toJSON());
        delete table;
        return ret;
      } else {
        qCritical() << tr("Could not query table data of id %1!").arg(tableId);
      }
    } else {
      qCritical() << tr("Could not convert table id '%1' to an integer!")
                         .arg(request->dataName());
    }
  } break;
  case ComPackage::RequestOrderOnTable: {
    bool ok;
    int tableId = request->dataName().toInt(&ok);
    if (ok) {
      QList<int> ids;
      if (_db.orderIds(ids, tableId)) {
        QJsonArray arr;
        foreach (int id, ids) {
          Order *order = _db.order(id, _waiterList[client]);
          if (order) {
            arr.append(order->toJSON());
            delete order;
          } else
            qCritical() << tr("Could not query order from id %1!").arg(id);
        }
        QJsonValue jsonVal(arr);

        return new ComPackageDataReturn(*request, jsonVal);
      } else {
        qCritical()
            << tr("Could not query order ids for table %1!").arg(tableId);
      }
    } else {
      qCritical() << tr("Could not convert table id '%1' to an integer!")
                         .arg(request->dataName());
    }
  }
  // Not implemented yet, for admin app perhaps
  case ComPackage::RequestOrderIds:
    break;
  case ComPackage::RequestOrder: {
    bool ok;
    int orderId = request->dataName().toInt(&ok);
    if (ok) {
      Order *order = _db.order(orderId, _waiterList[client]);
      if (order) {
        ComPackageDataReturn *ret =
            new ComPackageDataReturn(*request, order->toJSON());
        delete order;
        return ret;
      } else {
        qCritical() << tr("Could not query order data of id %1!").arg(orderId);
      }
    } else {
      qCritical() << tr("Could not convert order id '%1' to an integer!")
                         .arg(request->dataName());
    }
  } break;
  case ComPackage::RequestCategory: {
    bool ok;
    int categoryId = request->dataName().toInt(&ok);
    if (ok) {
      ProductCategory *category = _db.category(categoryId);
      if (category) {
        ComPackageDataReturn *ret =
            new ComPackageDataReturn(*request, category->toJSON());
        delete category;
        return ret;
      } else {
        qCritical()
            << tr("Could not query category data of id %1!").arg(categoryId);
      }
      delete category;
    } else {
      qCritical() << tr("Could not convert category id '%1' to an integer!")
                         .arg(request->dataName());
    }

  } break;
  case ComPackage::RequestProduct: {
    bool ok;
    int productId = request->dataName().toInt(&ok);
    if (ok) {
      Product *product = _db.product(productId);
      if (product) {
        ComPackageDataReturn *ret =
            new ComPackageDataReturn(*request, product->toJSON());
        delete product;
        return ret;
      } else {
        qCritical()
            << tr("Could not query product data of id %1!").arg(productId);
      }
      delete product;
    } else {
      qCritical() << tr("Could not convert product id '%1' to an integer!")
                         .arg(request->dataName());
    }

  } break;
  case ComPackage::RequestConfig: {
    ComPackageDataReturn *ret =
        new ComPackageDataReturn(*request, configToJSON());
    return ret;
  } break;
  case ComPackage::RequestLicence: {
    //      ComPackageDataReturn* ret = new ComPackageDataReturn(*request,
    //      QJsonValue(_licence->getLicenceStatus()));
    //      return ret;
  } break;
  case ComPackage::RequestIncome: {
    bool ok;
    int incomeId = request->dataName().toInt(&ok);
    if (ok) {
      Income *income;
      if (incomeId == -1)
        income = _db.getLastIncome();
      else
        income = _db.income(incomeId);
      if (income) {
        ComPackageDataReturn *ret =
            new ComPackageDataReturn(*request, income->toJSON());
        delete income;
        return ret;
      } else {
        qCritical()
            << tr("Could not query income data of id %1!").arg(incomeId);
      }
    } else {
      qCritical() << tr("Could not convert income id '%1' to an integer!")
                         .arg(request->dataName());
    }
  } break;
  case ComPackage::RequestUserIds: {
    if (ifAdmin(client)) {
      QList<int> ids;
      if (_db.userIds(ids)) {
        QJsonArray arr;
        foreach (int id, ids)
          arr.append(id);
        QJsonValue jsonVal(arr);
        return new ComPackageDataReturn(*request, jsonVal);
      } else
        qCritical() << tr("Could not query users ids for account type %1!")
                           .arg(rotable::ComPackage::TableAccount);
    }
  } break;
  case ComPackage::RequestUser:{
    if (ifAdmin(client)) {
      Client *user = _db.client(request->dataName().toInt());
      if (user) {
        ComPackageDataReturn *ret =
            new ComPackageDataReturn(*request, user->toJSON());
        delete user;
        return ret;
      } else {
        qCritical()
            << tr("Could not query income data of id %1!").arg(request->dataName().toInt());
      }
    }
  } break;
  default: {
    qCritical()
        << tr("Unknown data request id: %d").arg(request->dataCategory());
  } break;
  }

  return nullptr;
}

//------------------------------------------------------------------------------

bool Server::setData(ComPackageDataSet *set, client_t client) {
  switch (set->dataCategory()) {
  case ComPackage::SetImage: {
    return true;
  } break;
  case ComPackage::SetCategory: {
    ProductCategory *category = ProductCategory::fromJSON(set->data());

    if (category) {
      if (category->id() == -1) {
        return addCategory(category);
      } else {
        return updateCategory(category);
      }
    } else {
      return false;
    }
  } break;
  case ComPackage::SetProduct: {
    Product *product = Product::fromJSON(set->data());

    if (product) {
      if (product->id() == -1) {
        return addProduct(product);
      } else {
        return updateProduct(product);
      }
    } else {
      return false;
    }
  } break;
  case ComPackage::SetOrder: {
    bool status = false;
    if (set->dataName() == "") {
      // Covert data to array
      QJsonArray array = set->data().toArray();

      // Crete QList with items
      QList<OrderItem *> order;
      foreach (QJsonValue item, array) {
        order.append(OrderItem::fromJSON(item));
      }
      // Check if order create succesfull
      if (newOrder(order, _users[1][client])) {
        rotable::OrderMessage *msg = new rotable::OrderMessage(0);
        status = true;
        _tcp.send(client, *(msg->toPackage()));
      } else {
        rotable::OrderMessage *msg = new rotable::OrderMessage(1);
        status = false;
        _tcp.send(client, *(msg->toPackage()));
      }
    } else {
      Order *order = rotable::Order::fromJSON(set->data());
      status = updateOrder(order);
    }

    // If something change
    if (status)
      sendQueueOrders();

    return status;

  } break;

  case ComPackage::SetLicence: {
    QJsonArray arr = set->data().toArray(); // For store files
    QStringList name = {"licence.dat", "licence.crt"};
    auto path = QDir(_config.licence_path());
==== BASE ====
<<<<<<< Temporary merge branch 1
==== BASE ====
    int i  = 0; // i++?
==== BASE ====
==== BASE ====
=======

>>>>>>> /tmp/meld-tmp-Zdalne-Di4Da_

    foreach (QJsonValue file, arr) {
      QByteArray ba = QByteArray::fromBase64(file.toString().toLocal8Bit(),
                                             QByteArray::Base64UrlEncoding);
      if (i > name.length()) {
        qWarning() << "Recive more file that we can save!";
        return false;
      }
      QFile f(path.filePath(name[i++]));
      f.open(QIODevice::WriteOnly);
      f.write(ba);
      f.close();
    }
    //    _licence->loadLicence();
    return true;
  } break;

==== BASE ====
<<<<<<< Temporary merge branch 1
==== BASE ====
  case ComPackage::SetVideo:
  {
      QJsonArray arr = set->data().toArray();
      foreach(QJsonValue file, arr)
      {
          QByteArray ba = QByteArray::fromBase64(file.toString().toLocal8Bit(),
                                                 QByteArray::Base64UrlEncoding);
          QString info(ba);
          qWarning() << "Recived: ComPackage::SetVideo:"<<info;
      }
      return true;
      break;
  }

==== BASE ====
  default:
  {
==== BASE ====
=======
  default: {
>>>>>>> /tmp/meld-tmp-Zdalne-Di4Da_
    qCritical() << tr("Unknown data set id: %d").arg(set->dataCategory());
    return false;
  } break;
  }
}

//------------------------------------------------------------------------------

bool Server::addCategory(ProductCategory *category) {
  if (_db.hasCategory(category->name())) {
    qWarning() << tr("A product category of name '%1' already exists!")
                      .arg(category->name());
    return false;
  }

  if (!_db.addCategory(category)) {
    qWarning() << tr("Failed to add product category!");
    return false;
  }

  // Inform clients about data change...
  ComPackageDataChanged dc;
  dc.setDataCategory(ComPackage::RequestCategoryIds);
  _tcp.send(-1, dc);

  return true;
}

//------------------------------------------------------------------------------

bool Server::updateCategory(ProductCategory *category) {
  if (!_db.hasCategory(category->id())) {
    qWarning() << tr("A product category with id '%1' does not exists!")
                      .arg(category->id());
    return false;
  }

  if (!_db.updateCategory(category)) {
    qWarning() << tr("Failed to update product category!");
    return false;
  }

  // Inform clients about data change...
  ComPackageDataChanged dc;
  dc.setDataCategory(ComPackage::RequestCategory);
  dc.setDataName(QString("%1").arg(category->id()));
  _tcp.send(-1, dc);

  return true;
}

//------------------------------------------------------------------------------

bool Server::updateOrder(Order *order) {
  if (!_db.hasOrder(order->id())) {
    qWarning() << tr("A order with id '%1' does not exists!").arg(order->id());
    return false;
  }

  if (!_db.updateOrder(order)) {
    qWarning() << tr("Failed to update order!");
    return false;
  }

  // Inform clients about data change...
  ComPackageDataChanged dc;
  dc.setDataCategory(ComPackage::RequestOrder);
  dc.setDataName(QString("%1").arg(order->id()));
  send_to_users(dc, rotable::ComPackage::WaiterAccount);

  return true;
}

//------------------------------------------------------------------------------

bool Server::newOrder(QList<OrderItem *> orders, int clientId) {
  Order *order = new Order();
  // Add order item to order
  if (orders.count() == 0)
    return false;
  foreach (OrderItem *item, orders) {
    Product *item_detail = _db.product(item->productId());
    item->setPrice((double)(item_detail->price()) / 100 * item->amount());
    order->addItem(item);
  }
  // Set state of order
  order->setState(Order::Sent);
  // Set client id
  order->setClientId(clientId);

  // Add order
  if (!_db.addOrder(order))
    return false;

  ComPackageDataChanged dc;
  dc.setDataCategory(ComPackage::RequestOrderIds);
  dc.setDataName(QString("%1").arg(clientId));
  send_to_users(dc, rotable::ComPackage::WaiterAccount);

  return true;
}

//------------------------------------------------------------------------------

bool Server::addProduct(Product *product) {
  /*if (_db.hasProduct(product->name(), product->categoryId())) {
    qWarning() << tr("A product of name '%1' already exists!")
                  .arg(product->name());
    return false;
  }*/

  if (!_db.addProduct(product)) {
    qWarning() << tr("Failed to add product!");
    return false;
  }

  // Inform clients about data change...
  ComPackageDataChanged dc;
  dc.setDataCategory(ComPackage::RequestProductIds);
  dc.setDataName(QString("%1").arg(product->categoryId()));
  _tcp.send(-1, dc);

  return true;
}

//------------------------------------------------------------------------------

bool Server::updateProduct(Product *product) {
  if (!_db.hasProduct(product->id(), product->categoryId())) {
    qWarning()
        << tr("A product with id '%1' does not exists!").arg(product->id());
    return false;
  }

  if (!_db.updateProduct(product)) {
    qWarning() << tr("Failed to update product!");
    return false;
  }

  // Inform clients about data change...
  ComPackageDataChanged dc;
  dc.setDataCategory(ComPackage::RequestProduct);
  dc.setDataName(QString("%1").arg(product->id()));
  _tcp.send(-1, dc);

  return true;
}

//------------------------------------------------------------------------------

bool Server::addIncome(Income *income) {
  if (_db.hasIncome(income->date()) != -1) {
    qWarning() << tr("A income of date '%1' already exists!")
                      .arg(income->date().toString());
    return false;
  }

  if (!_db.addIncome(income)) {
    qWarning() << tr("Failed to add income!");
    return false;
  }

  // we don't need inform clients about changes...
  // in future we can inform admin app about change to update diagram
  // ToDo: inform admin app about change

  return true;
}

//------------------------------------------------------------------------------

bool Server::updateIncome(Income *income) {
  if (!_db.hasIncome(income->id())) {
    qWarning()
        << tr("A income with id '%1' does not exists!").arg(income->id());
    return false;
  }

  if (!_db.updateIncome(income)) {
    qWarning() << tr("Failed to update income!");
    return false;
  }

  // we don't need inform clients about changes...
  // in future we can inform admin app about change to update diagram
  // ToDo: inform admin app about change

  return true;
}

//------------------------------------------------------------------------------

bool Server::newIncome() {
  Income *income = new Income();
  income->setIncome(0.0);
  // ToDo: change here
  income->setDate(QDate::currentDate());

  return addIncome(income);
}

//------------------------------------------------------------------------------

bool Server::closeDay() {
  // Config not load, we can't closeDay
  if (_stateChange.toChange.count() == 0)
    return false;

  // We must load all orders witch are not done
  QList<Order *> *list;
  list = _db.getNotCloseOrderList();

  foreach (Order *order, *list) {
    for (int i = 0; ++i; order->itemCount())
      order->closeOrder(_stateChange.toChange, _stateChange.newState);

    if (!updateOrder(order))
      return false;
  }

  return true;
}

//------------------------------------------------------------------------------

bool Server::setWaiterNeed(bool need, int tableId) {
  if (_db.setWaiterNeed(need, tableId)) {
    ComPackageDataChanged dc;
    dc.setDataCategory(ComPackage::RequestTable);
    dc.setDataName(QString(tableId));
    send_to_users(dc, 2);
    return true;
  } else {
    return false;
  }
}

//------------------------------------------------------------------------------

bool Server::executeCommand(ComPackageCommand *package) {
  if (package) {
    switch (package->commandType()) {
    case ComPackage::ResetDatabase: {
      //      _tcp.close();
      _db.createDatabase();
      //      _tcp.start(_config.port());
      //       Inform clients about data change...

      ComPackageDataChanged dc;
      dc.setDataCategory(ComPackage::RequestCategoryIds);

      _tcp.send(-1, dc);
      send_to_users(dc, 1);
      return true;
    } break;
    case ComPackage::DeleteCategory: {
      int categoryId = package->data().toInt(-1);
      if (categoryId == -1) {
        qCritical() << tr(
            "Could not parse categoryId from DeleteCategory command.");
      } else {
        if (_db.removeCategory(categoryId)) {
          // Inform clients about data change...
          ComPackageDataChanged dc;
          dc.setDataCategory(ComPackage::RequestCategoryIds);
          _tcp.send(-1, dc);
          send_to_users(dc, 1);
          return true;
        }
      }
    } break;
    case ComPackage::DeleteProduct: {
      int productId = package->data().toInt(-1);
      if (productId == -1) {
        qCritical() << tr(
            "Could not parse productId from DeleteProduct command.");
        return false;
      } else {
        Product *product = _db.product(productId);

        if (0 == product) {
          qCritical()
              << tr("Product with id '%1' does not exist!").arg(productId);
          return false;
        }

        if (_db.removeProduct(productId)) {
          // Inform clients about data change...
          ComPackageDataChanged dc;
          dc.setDataCategory(ComPackage::RequestProductIds);
          dc.setDataName(QString::number(product->categoryId()));
          _tcp.send(-1, dc);
          send_to_users(dc, 1);
          return true;
        }
      }
    } break;
    case ComPackage::SetLicencePath: {
      QString path = package->data().toString();
      _config.setLicence_path(path);
    } break;
    case ComPackage::CommandType::CreateUser: {
      User *user = reinterpret_cast<User*>(Client::fromJSON(package->data()));
      if(_db.addUser(user)){
        // Inform admins about data change...
        ComPackageDataChanged dc;
        dc.setDataCategory(ComPackage::RequestUserIds);
        send_to_users(dc, 2);
        return true;
      }

    } break;
    case ComPackage::CommandType::AddWaiterCategory:
    {
      QJsonArray  arr = package->data().toArray();
      QList<int> list;
      list.append(arr[1].toInt());
      if(_db.addWaiterCategoires(arr[0].toInt(), &list)){
        // Inform admins about data change...
        ComPackageDataChanged dc;
        dc.setDataCategory(ComPackage::RequestUser);
        dc.setDataName(QString("%1").arg(arr[0].toInt()));
        send_to_users(dc, 2);
        return true;
      }
    } break;
    case ComPackage::CommandType::RemoveWaiterCategory: {
      QJsonArray  arr = package->data().toArray();
      QList<int> list;
      list.append(arr[1].toInt());
      if(_db.removeWaiterCategoires(arr[0].toInt(), &list)){
        // Inform admins about data change...
        ComPackageDataChanged dc;
        dc.setDataCategory(ComPackage::RequestUser);
        dc.setDataName(QString("%1").arg(arr[0].toInt()));
        send_to_users(dc, 2);
        return true;
      }  
    } break;
    case ComPackage::CommandType::ChangeClientName: {
      QJsonArray  arr = package->data().toArray();
      Client* user = _db.client(arr[0].toInt());
      user->setName(arr[1].toString());
      if(_db.updateClient(user)){
        return true;
      }
    } break;
    case ComPackage::CommandType::ChangePassword: {
      QJsonArray  arr = package->data().toArray();
      User* user = reinterpret_cast<User*>(_db.client(arr[0].toInt()));
      user->setHashPassword(arr[1].toString());
      if(_db.updateUserPassword(user)){
        return true;
      }
    } break;
    default: {
      qCritical()
          << tr("Unknown command type '%1'!").arg(package->commandType());
    } break;
    }
  }

  return false;
}

//------------------------------------------------------------------------------

bool Server::login(ComPackageConnectionRequest *package, client_t client) {
  //    qDebug() << "Anvalible account type" << endl
  //             << "Admin Account:" << QString(ComPackage::AdminAccount) <<
  //             endl
  //             << "Waiter Account:" << QString(ComPackage::WaiterAccount) <<
  //             endl
  //             << "Table Account: " << QString(ComPackage::TableAccount) <<
  //             endl;
  if (package) {
    switch (package->clientType()) {
    case rotable::ComPackage::WaiterAccount:
    case rotable::ComPackage::AdminAccount: {
      // Get waiter id
      int id = _db.hasUser(package->clientName(), package->clientPass());
      if (id < 1) // If id < 0 then loggin failed, we can end it
        return false;
      _users[package->clientType()].insert(client, id);
      if(package->clientType() == rotable::ComPackage::WaiterAccount)
      {
        Waiter *waiter = reinterpret_cast<Waiter*>(_db.client(id));
        _waiterList[client] = waiter;
      }
      return true;
    }
    case rotable::ComPackage::TableAccount: {
      int id = _db.registerTable(package->clientName(), package->clientPass());
      _users[package->clientType()].insert(client, id);

      // Prepare packahe inform waiters that, table count are chagne;
      ComPackageDataChanged dc;
      dc.setDataCategory(ComPackage::RequestTableIds);
      send_to_users(dc, rotable::ComPackage::WaiterAccount);

      return true;
    }
    default: {
      qCritical()
          << tr("Unknown account type '%1'!").arg(package->clientType());
      return false;
    }
    }
  }
  return 0;
}

//------------------------------------------------------------------------------

void Server::send_to_users(ComPackage &package, int accountType) {
  foreach (client_t client, _users[accountType].keys()) {
    _tcp.send(client, package);
  }
}

//------------------------------------------------------------------------------

void Server::load_configs() {
  qDebug() << "Load configs";
  QList<int> ids;     // List for config id
  _db.configIds(ids); // Get config ids from database
  // For any id in ids list
  foreach (int id, ids) {
    qDebug() << "Load config with id:" << id << endl;
    Config *cfg = _db.config(id); // Load config from dababase (base on id)
    config_parser(cfg);           // Parse config
    delete cfg;                   // Delete obj;
  }
}

//------------------------------------------------------------------------------

void Server::config_parser(Config *config) {
  // Base on config name we select prepare method
  switch (config->name()) {
  case Config::day_begin:
    day_begin_config(config);
    break;
  case Config::closeState:
    closeStateConfig(config);
    break;
  case Config::dbVersion:
    break;
  default:
    qCritical() << tr("Unknown config type '%1'!").arg(config->name());
  }
}

//------------------------------------------------------------------------------

void Server::day_begin_config(Config *config) {

  // Load last income from database
  Income *lastIncome = _db.getLastIncome();

  // Prepare date f add new income to database
  QDateTime dateTime;
  if (!lastIncome) // If income don't exist
  {
    // We want add new income record with day before today
    dateTime = QDateTime::currentDateTime(); // current day(today)
    dateTime = dateTime.addDays(-1);         // yesterday
  } else {
    dateTime.setDate(lastIncome->date()); // last income day
    dateTime = dateTime.addDays(1);       // next income day
  }
  // Read time from config
  QTime time = QTime::fromString(config->value(), "hh:mm");
  // Create new ScheduleOperation obj
  ScheduleOperation *operation = new ScheduleOperation();
  // Init filds of class
  operation->setName("day_begin");
  // qDebug() << "time load from config" << time.toString("hh:m") << endl<<
  // "String with data" << config->value() << endl;
  dateTime.setTime(time);
  operation->setNext(dateTime);
  operation->setDayInterval(1);

  // We can call many operation at once
  // Connect signal emit on time with method on server(create new income)
  connect(operation, &ScheduleOperation::on_time, this, &Server::newIncome);
  // ^^ Close day
  connect(operation, &ScheduleOperation::on_time, this, &Server::closeDay);
  // the easiest way is the best xD

  // Add operation to schedule
  schedule->addOperiationToSchedule(operation);
}

//------------------------------------------------------------------------------

void Server::closeStateConfig(Config *config) {
  // exp. "1,2,3;4"
  QStringList tmpList = config->value().split(";");

  // If we haven't 2 element after split close
  if (tmpList.count() != 2)
    return;

  // First element
  // we have "1,2,3" => 1, 2, 3

  QList<int> toCloseList; // Store states
  bool ok;                // To convert

  foreach (QString element, tmpList[0]) {

    int state = element.toInt(&ok);

    if (!ok) // Something is wrong, close
      return;

    toCloseList.append(state);
  }

  int newState = tmpList[1].toInt(&ok);
  if (!ok) // Something is wrong, close
    return;

  // Set new value
  _stateChange.toChange = toCloseList;
  _stateChange.newState = newState;
}

//------------------------------------------------------------------------------

QMap<int, ComPackageMessage *> Server::queueOrders() {
  QMap<int, ComPackageMessage *> result;
  //    QMap<int, QMap<int, int> > orderList;
  QMap<int, QMap<int, int>>::iterator it;

  //    QList<rotable::Order*> *idList = _db.getNotDoneOrderList();
  //    if(idList == NULL)
  //        return result;
  //    int i = 1;
  //    foreach(Order* order, *idList)
  //    {
  //        orderList[order->clientId()][i] = order->id();
  //        ++i;
  //    }
  //    delete idList;

  QMap<int, QMap<int, int>> *queue = _db.getOrderQueueList();

  if (queue) {
    it = queue->begin();
    while (it != queue->end()) {
      QueueMessage msg(it.value());
      result[it.key()] = msg.toPackage();
      ++it;
    }

    delete queue;
  }

  return result;
}

//------------------------------------------------------------------------------

void Server::sendQueueOrders() {
  QMap<int, ComPackageMessage *> queue(queueOrders());
  QMap<int, ComPackageMessage *>::iterator it = queue.begin();
  QList<int> emptyTable;

  foreach (int userId, _users[1]) {
    if (!queue.contains(userId))
      emptyTable.append(userId);
  }

  while (it != queue.end()) {
    if (_users[1].keys(it.key()).count() == 1)
      _tcp.send(_users[1].keys(it.key())[0], *(it.value()));
    ++it;
  }
}

//------------------------------------------------------------------------------

bool Server::ifAdmin(int connection) const {
  if (_users[2].contains(connection))
    return true;
  return false;
}

//------------------------------------------------------------------------------

void Server::updateWaiterCategories(int waiterId, int categoryId, int type)
{
  for(auto waiter: _waiterList)
  {
    if(waiter->id() == waiterId)
    {
      if(type == 1)
        waiter->addWaiterCategory(categoryId);
      else
        waiter->removeWaiterCategory(categoryId);
    }
  }
}

//------------------------------------------------------------------------------

QJsonValue Server::configToJSON() {
  auto path = _config.licence_path();
  return QJsonValue(path);
}

//------------------------------------------------------------------------------

bool Server::kindOfFileDestination(ComPackageSendFile* package)
{
    if (package) {
      switch (package->getFileUsage()) {
      case ComPackage::AdvertisingVideo:
          LogManager::getInstance()->logInfo("\n\n hier\n\n");

          break;
      case ComPackage::AdvertisingPicture:

          break;
      case ComPackage::CatergoryIcon:

          break;
      case ComPackage::ProductIcon:

          break;



      }
    }
    return true;
}

