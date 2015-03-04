#include "private/precomp.h"

#include "server.h"
#include "settings.h"
#include "logmanager.h"

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
}

//------------------------------------------------------------------------------

Server::~Server()
{

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

  }

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
    _tcp.setClientName(client, p->clientName());

    ComPackageConnectionAccept accept;
    _tcp.send(client, accept);
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
  case ComPackage::Login:
  {
    if (_tcp.isClientAccepted(client)) {
      ComPackageLogin* p = static_cast<ComPackageLogin*>(package);

      ComPackageDataReturn* ret = login(p, client);
      if (ret) {
        _tcp.send(client, *ret);
      } else {
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

  // Find client in map
  QMap<client_t, int>::Iterator it = _waiters.find(client);
  // if client is in map (client is a waiter), remove client from list
  if (it != _waiters.end())
      _waiters.erase(it);
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

ComPackageDataReturn* Server::login(ComPackageLogin* package, client_t client)
{
    if(package)
    {
        switch (package->loginType()) {
        case ComPackage::WaiterAccount :
        {
            // Load data about waiter from Json
            Waiter *w = Waiter::fromJSON(package->data());
            // Get waiter id
            int id = _db.hasWaiter(w->nick(),w->hashPassword());
            if(!id) // If id < 0 then loggin failed, we can end it
                return 0;
            _waiters.insert(client, id);
            // clean memory, we don't like memory leaks
            delete w;
            // get waiter data, base on id
            w = _db.waiter(id);
            // we don't need password any more, delate for safety
            w->setHashPassword("");


            // return data about waiter
            ComPackageDataReturn *pkg = new ComPackageDataReturn();
            pkg->setData(w->toJSON());
            pkg->setDataCategory(ComPackage::RequestWaiter);
            return pkg;
        }   break;
        default:
        {
          qCritical() << tr("Unknown account type '%1'!").arg(package->loginType());
          return 0;
        } break;
        }
    }
    return 0;
}

void Server::send_to_waiters(ComPackage &package)
{
    foreach (client_t client, _waiters.keys()) {
        _tcp.send(client, package);
    }
}



//------------------------------------------------------------------------------
