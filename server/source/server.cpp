#include "private/precomp.h"

#include "server.h"
#include "settings.h"
#include "logmanager.h"
#include "productorder.h"

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
}

//------------------------------------------------------------------------------

Server::~Server()
{
    delete schedule;
}

//------------------------------------------------------------------------------

bool Server::startup()
{
  if (_config.error() != NoError) {
    qCritical() << tr("Config file error: %1").arg(_config.errorStr());
    return false;
  }

  _images.clear();

  if (!_db.startConnection(ROTABLE_DATABASE_CLIENT,
                           _config.db_host(), _config.db_name(),
                           _config.db_user(), _config.db_pass(),
                           _config.db_prefix()))
  {
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
    }

  }  qDebug()<<"test";

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

void Server::createDatabase()
{
  if (!_db.createDatabase()) {
    qCritical() << tr("Could not create database!");
  }
}

//------------------------------------------------------------------------------

void Server::clientConnected(client_t client)
{
  qDebug() << tr("Client connected: %1").arg(
                  _tcp.clientSocket(client)->peerAddress().toString());
}

//------------------------------------------------------------------------------

void Server::packageReceived(client_t client, ComPackage *package)
{
  switch (package->type()) {
  case ComPackage::ConnectionRequest:
  {
    ComPackageConnectionRequest* p = static_cast<ComPackageConnectionRequest*>(package);
    if (login(p, client)) {
      _tcp.setClientName(client, p->clientName());
      ComPackageConnectionAccept accept;
      _tcp.send(client, accept);
    } else {
      ComPackageReject reject(package->id());
      _tcp.send(client, reject);
    }
  } break;
  case ComPackage::ConnectionAccept:
  {
    qDebug() << tr("Did not expect to receive ConnectionAccept package... rejecting");
    ComPackageReject reject(package->id());
    _tcp.send(client, reject);
  } break;
  case ComPackage::DataRequest:
  {
    if (_tcp.isClientAccepted(client)) {
      ComPackageDataRequest* p = static_cast<ComPackageDataRequest*>(package);

      ComPackageDataReturn* ret = getData(p);
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
  case ComPackage::DataReturn:
  {
    qDebug() << tr("Did not expect to receive DataReturn package... rejecting");
    ComPackageReject reject(package->id());
    _tcp.send(client, reject);
  } break;
  case ComPackage::DataChanged:
  {
    qDebug() << tr("Did not expect to receive DataChanged package... rejecting");
    ComPackageReject reject(package->id());
    _tcp.send(client, reject);
  } break;
  case ComPackage::DataSet:
  {
    if (_tcp.isClientAccepted(client)) {
      ComPackageDataSet* p = static_cast<ComPackageDataSet*>(package);

      if (!setData(p)) {
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
  case ComPackage::Command:
  {
    if (_tcp.isClientAccepted(client)) {
      ComPackageCommand* p = static_cast<ComPackageCommand*>(package);

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
  case ComPackage::Reject:
  {
    qDebug() << tr("Did not expect to receive Reject package... doing nothing");
  } break;
  }
}

//------------------------------------------------------------------------------

void Server::clientDisconnected(client_t client, const QString &clientName)
{
  qDebug() << tr("Client %1 disconnected").arg(clientName);

  // remove client from _users
  // we don't know in with QMap it is
  // so we remove element from all QMap
  for(int i=0; i<3;++i)
    _users[i].remove(client);

}

//------------------------------------------------------------------------------

ComPackageDataReturn *Server::getData(ComPackageDataRequest *request)
{
  switch (request->dataCategory())
  {
  case ComPackage::RequestImage:
  {
    if (_images.contains(request->dataName())) {
      const QImage& img = _images[request->dataName()].img;

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
  case ComPackage::RequestCategoryIds:
  {
    QList<int> ids;
    if (_db.categoryIds(ids)) {
      QJsonArray arr;
      foreach (int id, ids) {
        arr.append(id);
      }
      QJsonValue jsonVal(arr);

      return new ComPackageDataReturn(*request, jsonVal);
    } else {
      qCritical() << tr("Could not query product category ids!");
    }
  } break;
  case ComPackage::RequestProductIds:
  {
    bool ok;
    int categoryId = request->dataName().toInt(&ok);
    if (ok) {
      QList<int> ids;
      if (_db.productIds(ids, categoryId)) {
        QJsonArray arr;
        foreach (int id, ids) {
          arr.append(id);
        }
        QJsonValue jsonVal(arr);

        return new ComPackageDataReturn(*request, jsonVal);
      } else {
        qCritical() << tr("Could not query product ids for category %1!").arg(categoryId);
      }
    } else {
      qCritical() << tr("Could not convert category id '%1' to an integer!")
                     .arg(request->dataName());
    }
  } break;
  case ComPackage::RequestCategory:
  {
    bool ok;
    int categoryId = request->dataName().toInt(&ok);
    if (ok) {
      ProductCategory* category = _db.category(categoryId);
      if (category) {
        ComPackageDataReturn* ret = new ComPackageDataReturn(*request, category->toJSON());
        delete category;
        return ret;
      } else {
        qCritical() << tr("Could not query category data of id %1!")
                       .arg(categoryId);
      }
    } else {
      qCritical() << tr("Could not convert category id '%1' to an integer!")
                     .arg(request->dataName());
    }
  } break;
  case ComPackage::RequestProduct:
  {
    bool ok;
    int productId = request->dataName().toInt(&ok);
    if (ok) {
      Product *product = _db.product(productId);
      if (product) {
        ComPackageDataReturn* ret = new ComPackageDataReturn(*request, product->toJSON());
        delete product;
        return ret;
      } else {
        qCritical() << tr("Could not query product data of id %1!")
                       .arg(productId);
      }
    } else {
      qCritical() << tr("Could not convert product id '%1' to an integer!")
                     .arg(request->dataName());
    }
  } break;
  default:
  {
    qCritical() << tr("Unknown data request id: %d").arg(request->dataCategory());
  } break;
  }

  return 0;
}

//------------------------------------------------------------------------------

bool Server::setData(ComPackageDataSet *set)
{
  switch (set->dataCategory())
  {
  case ComPackage::SetImage:
  {
    return true;
  } break;
  case ComPackage::SetCategory:
  {
    ProductCategory* category = ProductCategory::fromJSON(set->data());

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
  case ComPackage::SetProduct:
  {
    Product* product = Product::fromJSON(set->data());

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
  case ComPackage::SetProductOrder:
  {
    //ProductOrder* po = ProductOrder::fromJSON(set->data());
    //return updateOrders(po);
  }break;
  default:
  {
    qCritical() << tr("Unknown data set id: %d").arg(set->dataCategory());
    return false;
  } break;
  }
}

//------------------------------------------------------------------------------

bool Server::addCategory(ProductCategory *category)
{
  if (_db.hasCategory(category->name())) {
    qWarning() << tr("A product category of name '%1' already exists!").arg(category->name());
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

bool Server::updateCategory(ProductCategory *category)
{
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

bool Server::updateOrders(ProductOrder *order)
{
    //Some valid here
//    if (!_db.has) {
//      qWarning() << tr("A does not exists!")
//                    .arg(category->id());
//      return false;
//    }

    if (!_db.updateOrders(order)) {
      qWarning() << tr("Failed to update orders!");
      return false;
    }

    // Inform clients about data change...
//    ComPackageDataChanged dc;
//    dc.setDataCategory();
//    dc.setDataName(QString("%1").arg());
//    _tcp.send(-1, dc);
    return true;
}

//------------------------------------------------------------------------------

bool Server::addProduct(Product *product)
{
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

bool Server::updateProduct(Product *product)
{
  if (!_db.hasProduct(product->id(), product->categoryId())) {
    qWarning() << tr("A product with id '%1' does not exists!")
                  .arg(product->id());
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

bool Server::addIncome(Income *income)
{
    if (_db.hasIncome(income->date()) != -1) {
      qWarning() << tr("A income of date '%1' already exists!").arg(income->date().toString());
      return false;
    }

    if (!_db.addIncome(income)) {
      qWarning() << tr("Failed to add income!");
      return false;
    }

    // we don't need inform clients about changes...
    // in future we can inform admin app about change to update diagram
    //ToDo: inform admin app about change

    return true;
}

//------------------------------------------------------------------------------

bool Server::updateIncome(Income *income)
{
    if (!_db.hasIncome(income->id())) {
      qWarning() << tr("A income with id '%1' does not exists!")
                    .arg(income->id());
      return false;
    }

    if (!_db.updateIncome(income)) {
      qWarning() << tr("Failed to update income!");
      return false;
    }

    // we don't need inform clients about changes...
    // in future we can inform admin app about change to update diagram
    //ToDo: inform admin app about change

    return true;
}

//------------------------------------------------------------------------------

bool Server::newIncome()
{
    Income *income = new Income();
    income->setIncome(0.0);
    //ToDo: change here
    income->setDate(QDate::currentDate());

    return addIncome(income);
}

//------------------------------------------------------------------------------

bool Server::executeCommand(ComPackageCommand *package)
{
  if (package) {
    switch (package->commandType()) {
    case ComPackage::ResetDatabase:
    {
      _db.createDatabase();

      // Inform clients about data change...
      ComPackageDataChanged dc;
      dc.setDataCategory(ComPackage::RequestCategoryIds);
      _tcp.send(-1, dc);

      return true;
    } break;
    case ComPackage::DeleteCategory:
    {
      int categoryId = package->data().toInt(-1);
      if (categoryId == -1) {
        qCritical() << tr("Could not parse categoryId from DeleteCategory command.");
      } else {
        if (_db.removeCategory(categoryId)) {
          // Inform clients about data change...
          ComPackageDataChanged dc;
          dc.setDataCategory(ComPackage::RequestCategoryIds);
          _tcp.send(-1, dc);
          return true;
        }
      }
    } break;
    case ComPackage::DeleteProduct:
    {
      int productId = package->data().toInt(-1);
      if (productId == -1) {
        qCritical() << tr("Could not parse productId from DeleteProduct command.");
        return false;
      } else {
        Product* product = _db.product(productId);

        if (0 == product) {
          qCritical() << tr("Product with id '%1' does not exist!").arg(productId);
          return false;
        }

        if (_db.removeProduct(productId)) {
          // Inform clients about data change...
          ComPackageDataChanged dc;
          dc.setDataCategory(ComPackage::RequestProductIds);
          dc.setDataName(QString::number(product->categoryId()));
          _tcp.send(-1, dc);
          return true;
        }
      }
    } break;
    default:
    {
      qCritical() << tr("Unknown command type '%1'!").arg(package->commandType());
      return false;
    } break;
    }
  }

  return false;
}

//------------------------------------------------------------------------------

bool Server::login(ComPackageConnectionRequest* package, client_t client)
{
//    qDebug() << "Anvalible account type" << endl
//             << "Admin Account:" << QString(ComPackage::AdminAccount) << endl
//             << "Waiter Account:" << QString(ComPackage::WaiterAccount) << endl
//             << "Table Account: " << QString(ComPackage::TableAccount) << endl;
    if(package)
    {
        switch (package->clientType()) {
        case rotable::ComPackage::WaiterAccount :
        case rotable::ComPackage::AdminAccount :
        {
            // Get waiter id
            int id = _db.hasUser(package->clientName(),package->clientPass());
            if(id<1) // If id < 0 then loggin failed, we can end it
                return false;
            _users[package->clientType()].insert(client, id);
            return true;
        }
        case rotable::ComPackage::TableAccount :
            //_users[package->clientType()].insert(client, id);
            return true;
        default:
        {
          qCritical() << tr("Unknown account type '%1'!").arg(package->clientType());
          return false;
        }
        }
    }
    return 0;
}

//------------------------------------------------------------------------------

void Server::send_to_users(ComPackage &package, int accountType)
{
    foreach (client_t client, _users[accountType].keys()) {
        _tcp.send(client, package);
    }
}

//------------------------------------------------------------------------------

void Server::load_configs()
{
    qDebug() << "Load configs";
    QList<int> ids; // List for config id
    _db.configIds(ids);   // Get config ids from database
    // For any id in ids list
    foreach (int id, ids) {
        qDebug()<< "Load config with id:" <<  id << endl;
        Config *cfg =  _db.config(id);  // Load config from dababase (base on id)
        config_parser(cfg);             // Parse config
        delete cfg;                     // Delete obj;
    }
}

//------------------------------------------------------------------------------

void Server::config_parser(Config *config)
{
    // Base on config name we select prepare method
    switch (config->name()) {
    case Config::day_begin:
        day_begin_config(config);
        break;
    default:
        qCritical() << tr("Unknown config type '%1'!").arg(config->name());
    }
}

//------------------------------------------------------------------------------

void Server::day_begin_config(Config *config){

    //Load last income from database
    Income *lastIncome = _db.getLastIncome();

    //Prepare date f add new income to database
    QDateTime dateTime;
    if (!lastIncome)    // If income don't exist
    {
        //We want add new income record with day before today
        dateTime = QDateTime::currentDateTime();    //current day(today)
        dateTime = dateTime.addDays(-1);                       //yesterday
    }
    else
    {
       dateTime.setDate(lastIncome->date());       //last income day
       dateTime = dateTime.addDays(1);                        //next income day
    }
    //Read time from config
    QTime time = QTime::fromString(config->value(), "hh:mm");
    //Create new ScheduleOperation obj
    ScheduleOperation *operation =  new ScheduleOperation();
    //Init filds of class
    operation->setName("day_begin");
    //qDebug() << "time load from config" << time.toString("hh:m") << endl<< "String with data" << config->value() << endl;
    dateTime.setTime(time);
    operation->setNext(dateTime);
    operation->setDayInterval(1);
    //Connect signal emit on time with method on server(create new income)
    connect(operation, &ScheduleOperation::on_time,this, &Server::newIncome);
    //the easiest way is the best xD

    //Add operation to schedule
    schedule->addOperiationToSchedule(operation);
}

//------------------------------------------------------------------------------
