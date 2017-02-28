#include "private/precomp.h"

#include "addnewlicence.h"
#include "addproductcategory.h"
#include "addproductdialog.h"
#include "adduserdialog.h"
#include "connecttoserverdialog.h"
#include "executor.h"
#include "mainwindow.h"
#include "productcategory.h"
#include "productcontainer.h"
#include "resetpassword.h"
#include "utils.h"
#include "waitercategories.h"

#include <QBuffer>

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

Executor::Executor(MainWindow *mainwindow, const QString &configFilePath,
                   QObject *parent)
    : QObject(parent), _mainwindow(mainwindow), _config(configFilePath),
      _disconnectRequested(false), _images(0), _products(0), _tryLogin(false) {

  _addNewVideo= new AddNewVideo(_mainwindow);
  connect(&_tcp_client, SIGNAL(connected()), this,
          SLOT(onConnectionEstablished()));
  connect(&_tcp_client, SIGNAL(disconnected()), this, SLOT(onConnectionLost()));
  connect(&_tcp_client, SIGNAL(disconnected()), this, SIGNAL(connectionLost()));

  connect(&_tcp_client, SIGNAL(packageReceived(rotable::ComPackage *)), this,
          SLOT(onPackageReceived(rotable::ComPackage *)));
  connect(&_tcp_client, SIGNAL(error(QAbstractSocket::SocketError)), this,
          SLOT(onClientError(QAbstractSocket::SocketError)));
  connect(&_tcp_client, SIGNAL(progressBar(int, int)), this,
          SLOT(SendProgressBarType(int, int)));
  connect(&_serverLogListener, SIGNAL(connectionEstablished()), this,
          SIGNAL(serverLogConnectionEstablished()));
  connect(&_serverLogListener, SIGNAL(disconnected()), this,
          SIGNAL(serverLogConnectionLost()));
  connect(&_serverLogListener, SIGNAL(log(rotable::LogManager::LogMessage)),
          this, SIGNAL(serverLog(rotable::LogManager::LogMessage)));

  //  if (NoError != _config.load(configFilePath)) {
  //    qDebug() << tr("Could not load %1:
  //    %2").arg(configFilePath).arg(_config.errorStr());
  //  }

}

//------------------------------------------------------------------------------

void Executor::setImageContainer(ImageContainer *images) { _images = images; }

//------------------------------------------------------------------------------

void Executor::setProductContainer(ProductContainer *products) {
  _products = products;
}

//------------------------------------------------------------------------------

void Executor::setUserContainer(UserContainter *users) { _users = users; }

//------------------------------------------------------------------------------

void Executor::setFileContainer(rotable::AdvertisingContainer *file) { _files = file; }

//------------------------------------------------------------------------------

void Executor::onConnectToServer() {
  ConnectToServerDialog dlg(_mainwindow);

  dlg.setServerAddress(_config.serverAddress());
  dlg.setServerPort(_config.serverPort());
  dlg.setUsername(_config.adminName());

  if (dlg.exec() == QDialog::Accepted) {
    _username = dlg.username();
    _password = dlg.password();
    emit statusMessage(tr("Connecting to %1:%2")
                           .arg(dlg.serverAddress())
                           .arg(dlg.serverPort()));

    _config.setServerAddress(dlg.serverAddress());
    _config.setServerPort(dlg.serverPort());
    _config.setServerAdminName(dlg.username());

    _tcp_client.startConnection(dlg.serverAddress(), dlg.serverPort());


  }
}

//------------------------------------------------------------------------------

void Executor::onDisconnectFromServer() {
  _disconnectRequested = true;
  _tcp_client.closeConnection();

  emit statusMessage(tr("Disconnected"));
}

//------------------------------------------------------------------------------

void Executor::onAddProductCategory() {
  AddProductCategory dlg(_images, _mainwindow);
  dlg.setProductContainer(_products);

  if (dlg.exec() == QDialog::Accepted) {
    ProductCategory pc;
    pc.setName(dlg.categoryName());
    pc.setIcon(dlg.iconName());
    pc.setId(-1); // mark as new category
    pc.setSequence(_products->categoryIds().count() + 1);

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

void Executor::onAddUser() {
  AddUserDialog dlg(_mainwindow);
  rotable::User *user;
  if (dlg.exec() == QDialog::Accepted) {
    switch (dlg.accountType()) {
    case 0: {
      user = new Waiter();
    } break;

    case 1: {
      user = new Admin();
    } break;
    }

    user->setName(dlg.name());
    user->setPassword(dlg.password());

    ComPackageCommand pc;
    pc.setCommandType(rotable::ComPackage::CommandType::CreateUser);
    pc.setData(user->toJSON());
    delete user;

    if (!_tcp_client.send(pc)) {
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

void Executor::onWaiterCategoriesChange() {
  Waiter *waiter = reinterpret_cast<Waiter *>(_users->getSelectedUser());
  if (!waiter)
    return;
  WaiterCategories dlg(_products, waiter, _mainwindow);
  qDebug()<<_products;
  dlg.show();

  if (dlg.exec() == QDialog::Accepted) {
  }
}

//------------------------------------------------------------------------------

void Executor::onUpdateCategory(ProductCategory *category) {
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

void Executor::onAddProduct() {
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
    p.setSequence(_products->productIds(dlg.categoryId()).count() + 1);

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

void Executor::onChangePassword() {
  ResetPassword dlg(_mainwindow);

  if (dlg.exec() == QDialog::Accepted) {
    _users->getSelectedUser()->setPassword(dlg.password());
  }
}

//------------------------------------------------------------------------------

void Executor::onUpdateProduct(Product *product) {
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

void Executor::onUpdateClient() {
  Client *client = reinterpret_cast<Client *>(sender());

  ComPackageCommand command;
  command.setCommandType(ComPackage::ChangeClientName);
  QJsonArray arr;
  arr.append(client->id());
  arr.append(client->name());
  command.setData(arr);

  if (!_tcp_client.send(command)) {
    qCritical() << tr("FATAL: Could not send data set package!");
  }
}

//------------------------------------------------------------------------------

void Executor::onUpdateUserPassword() {
  User *user = reinterpret_cast<User *>(sender());

  ComPackageCommand command;
  command.setCommandType(ComPackage::ChangePassword);
  QJsonArray arr;
  arr.append(user->id());
  arr.append(user->hashPassword());
  command.setData(arr);

  if (!_tcp_client.send(command)) {
    qCritical() << tr("FATAL: Could not send data set package!");
  }
}

//------------------------------------------------------------------------------

void Executor::onResetDatabase() {
  QMessageBox msgBox;
  msgBox.setText(tr("This operation will clear your entire database. Are you "
                    "sure you want to continue?"));
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


void Executor::onUpdateAdvertisingVideo(AdvertisingVideo* advertisingVideo)
{
    if (advertisingVideo) {
      ComPackageDataSet set;
      set.setDataCategory(ComPackage::SetAdvertising);
      set.setData(advertisingVideo->toJSON());

      if (!_tcp_client.send(set)) {
        qCritical() << tr("FATAL: Could not send data set package!");
      }
    }
}

void Executor::onUpdateFrequencePlayTime(int changedFrequenceAdvertising)
{
    if(changedFrequenceAdvertising!=_dataBaseFrequnceAdvertising){
        ComPackageDataSet set;
        set.setDataCategory(ComPackage::SetAdvertisingConfig);
        set.setData(changedFrequenceAdvertising);

        if (!_tcp_client.send(set)) {
          qCritical() << tr("FATAL: Could not send data set package!");
        }
    }
}

//------------------------------------------------------------------------------

void Executor::onExportDatabase() {}

//------------------------------------------------------------------------------

void Executor::onImportDatabase() {}

//------------------------------------------------------------------------------

void Executor::onRemoveCurrentEntry() {
  if (_selectedCategory) {
    ComPackageCommand com;

    if (_selectedProduct) {
      //_products->removeProduct(_selectedProduct);
      //_selectedProduct = 0;

      com.setData(_selectedProduct->id());
      com.setCommandType(ComPackage::DeleteProduct);
      QList<int> productIds =
          _products->productIds(_selectedProduct->categoryId());
      auto it = productIds.end();
      --it;
      while (*it != _selectedProduct->id()) {
        _products->product(*it)->up();
        --it;
      }
      _products->removeProduct(_selectedProduct);
    } else {
      //_products->removeCategory(_selectedCategory);
      //_selectedCategory = 0;

      com.setData(_selectedCategory->id());
      QList<int> categoryIds = _products->categoryIds();
      auto it = categoryIds.end();
      --it;
      while (*it != _selectedCategory->id()) {
        _products->category(*it)->up();
        --it;
      }

      com.setCommandType(ComPackage::DeleteCategory);
      _products->removeCategory(_selectedCategory);
      //      emit updateSequenceCategory(_selectedCategory->id());
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

void Executor::onRenameCurrentEntry() {}

//------------------------------------------------------------------------------

void Executor::onCategorySelectionChanged(int id) {
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

void Executor::onProductSelectionChanged(int id) {
  if (id == -1) {
    _selectedProduct = 0;
  } else {
    _selectedProduct = _products->product(id);
    Q_ASSERT(_selectedProduct);
  }
}

//------------------------------------------------------------------------------

void Executor::onAdvertisingVideoSelectionChanged(const int id) {
  if (1 == -1) {
      qCritical()<<"wrong id";
    _selectedAdvertisingVideo = 0;
  } else {
     _files->setSelectedFile(id);
    _selectedAdvertisingVideo =_files->getSelectedFile();
    //Q_ASSERT(_selectedAdvertisingVideo);
  }
}

//------------------------------------------------------------------------------

void Executor::onExportStatistic() { _mainwindow->exportPdf(); }

//------------------------------------------------------------------------------

void Executor::onClearDebugServerLog() { _mainwindow->clearDebugServerLog(); }

//------------------------------------------------------------------------------

void Executor::onStartDebugServerListening() {
  _serverLogListener.startConnection("127.0.0.1", 5001);
}

//------------------------------------------------------------------------------

void Executor::onStopDebugServerListening() {
  _serverLogListener.stopConnection();
}

//------------------------------------------------------------------------------

void Executor::onAddLicence() {
  AddNewLicence dlg(_mainwindow);

    if (dlg.exec() != QDialog::Accepted)
        return;
    ;
    QStringList fileList = dlg.getList();
    if(fileList.isEmpty())
            return;
    QJsonArray array;

  foreach (QString fileName, fileList) {

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    QByteArray ba;
    QBuffer buffer(&ba);

    ba = file.readAll();
    QString base64 = ba.toBase64(QByteArray::Base64UrlEncoding);

    array.append(QJsonValue(base64));
  }

  ComPackageDataSet package;
  package.setData(array);
  package.setDataCategory(ComPackage::SetLicence);
  if (!_tcp_client.send(package)) {
    qCritical() << tr("FATAL: Could not send data set package!");

    QMessageBox msgBox;
    msgBox.setText("Network I/O-Error!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
  }

}

//------------------------------------------------------------------------------

void Executor::onUpdateSystem() {
  SystemUpdateDialog dlg(_mainwindow);

  if (dlg.exec() != QDialog::Accepted)
        return;

  ComPackageCommand package;
  QJsonValue true_=QJsonValue(true);
  package.setData(true_);
  package.setCommandType(ComPackage::SetUpdate);
  if (!_tcp_client.send(package)) {
    qCritical() << tr("FATAL: Could not send data set package!");

    QMessageBox msgBox;
    msgBox.setText("Network I/O-Error!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
  }
}

//------------------------------------------------------------------------------

void Executor::onAddAdvertisingVideo()
{

    QStringList fileNameList;
    QStringList files;

      if (_addNewVideo->exec() != QDialog::Accepted)
          return;
      ;
    QStringList filePathList = _addNewVideo->getStringVideo();
    if(filePathList.isEmpty())
        return;

    ComPackageSendFile package;
    foreach(QString path, filePathList)
    {
        /*make a StringList of the names from the files*/
        QStringList splitPath=path.split("/");
        QString fileName=splitPath.last();
        fileNameList.append(fileName);

        /*make a StringList of files in base64*/
        QFile file(path);
        file.open(QIODevice::ReadOnly);

        QByteArray ba;
        QBuffer buffer(&ba);
        ba = file.readAll();
        package.byteArrayToBase64(ba);

    }


    package.setFileUsage(ComPackage::AdvertisingVideo);
    package.setFileNames(fileNameList);

    if (!_tcp_client.send(package)) {
      qCritical() << tr("FATAL: Could not send data set package!");



    QMessageBox msgBox;
    msgBox.setText("Network I/O-Error!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();

    }
}


//------------------------------------------------------------------------------

void Executor::onRemoveAdvertisingVideo() {

    qDebug()<<"bis hier klappt das mediaId: "<< _selectedAdvertisingVideo->getMedia_id();
  ComPackageCommand com;

  if (_selectedAdvertisingVideo) {

    com.setData(_selectedAdvertisingVideo->getMedia_id());
    com.setCommandType(ComPackage::RemoveAdvertisingVideo);


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

void Executor::onProductUp() {
  if (_selectedProduct) {
    auto sequence = _products->productSequence(_selectedProduct->categoryId());
    if (_selectedProduct->sequence() > 1) {
      Product *product_second =
          _products->product(sequence[_selectedProduct->sequence() - 1]);
      _selectedProduct->up();
      product_second->down();
      changingSelection(productModel);
    }
  }
}

//------------------------------------------------------------------------------

void Executor::onProductDown() {
  if (_selectedProduct) {
    auto sequence = _products->productSequence(_selectedProduct->categoryId());
    if (_selectedProduct->sequence() < sequence.count()) {
      Product *product_second =
          _products->product(sequence[_selectedProduct->sequence() + 1]);
      _selectedProduct->down();
      product_second->up();
      changingSelection(productModel);
    }
  }
}

//------------------------------------------------------------------------------

void Executor::onCategoryUp() {
  if (_selectedCategory) {
    auto sequence = _products->productCategorySequence();
    if (_selectedCategory->sequence() > 1) {
      ProductCategory *category_second =
          _products->category(sequence[_selectedCategory->sequence() - 1]);
      _selectedCategory->up();
      category_second->down();
      changingSelection(categoryModel);
    }
  }
}

//------------------------------------------------------------------------------

void Executor::onCategoryDown() {
  if (_selectedCategory) {
    auto sequence = _products->productCategorySequence();
    if (_selectedCategory->sequence() < sequence.count()) {
      ProductCategory *category_second =
          _products->category(sequence[_selectedCategory->sequence() + 1]);
      _selectedCategory->down();
      category_second->up();
      changingSelection(categoryModel);
    }
  }
}

//------------------------------------------------------------------------------
void Executor::changingSelection(tableModel model)
{
    QItemSelectionModel *selectionModel;
    QModelIndex topLeft;
    QModelIndex bottomRight ;

    switch (model){
    case productModel:
        selectionModel= _productTableView->selectionModel();
        topLeft = _productTableModel->index(_selectedProduct->sequence()-1, 0, QModelIndex());
        bottomRight = _productTableModel->index(_selectedProduct->sequence()-1, 0, QModelIndex());
        break;
    case categoryModel:
        selectionModel= _categoryTableView->selectionModel();
        topLeft = _categoryTableModel->index(_selectedCategory->sequence()-1, 0, QModelIndex());
        bottomRight = _categoryTableModel->index(_selectedCategory->sequence()-1, 0, QModelIndex());

        break;
    default:
        qCritical()<<"non exisiting model (selection changing)";
    }
    QItemSelection selection(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::Select);
}

//------------------------------------------------------------------------------

void Executor::handleSelectionChanged(const QItemSelection &selection) {
  if (selection.indexes().isEmpty())
    _users->setSelectedUser(nullptr);
  else
    _users->setSelectedUser(selection.indexes().first().row());

  userSelectionChange();
}

//------------------------------------------------------------------------------

void Executor::onClientError(QAbstractSocket::SocketError error) {
  QMessageBox msgBox;
  msgBox.setText(QString("Network Error: %1").arg(SocketErrorToString(error)));
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.setIcon(QMessageBox::Critical);
  msgBox.exec();
}

//------------------------------------------------------------------------------

void Executor::onConnectionEstablished() {
  ComPackageConnectionRequest request;
  request.setClientName(_username);
  request.setClientPass(_password);
  request.setClientType(rotable::ComPackage::AdminAccount);
  _tryLogin = true;

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

void Executor::onConnectionLost() {
  if (!_mainwindow->isClosing() && !_disconnectRequested) {
    QMessageBox msgBox;
    msgBox.setText("Connection to server lost.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIconPixmap(
        QPixmap(QStringLiteral(":/rotable/network-connect.png"))
            .scaledToHeight(32));
    msgBox.exec();
  }

  _products->clear();
  _users->clear();
  _disconnectRequested = false;
}

//------------------------------------------------------------------------------

void Executor::onPackageReceived(ComPackage *package) {
  if (package) {
    switch (package->type()) {
    case ComPackage::ConnectionRequest:
      qCritical() << tr("ERROR: Received ConnectionRequest package!");
      break;

    case ComPackage::ConnectionAccept:
      _tryLogin = false;
      emit connectionEstablished();
      emit statusMessage(tr("Connected"));
      requestCategoryIds();
      requestServerConfigs();
      requestLicenceStatus();
      requestClientIds();
      requestMediaIds();
      requestAdvertisingConfigs();
      //requestSystemVersions(); //get installed and available Version
      break;

    case ComPackage::DataRequest:
      qCritical() << tr("ERROR: Received DataRequest package!");
      break;

    case ComPackage::DataReturn:
      dataReturned(static_cast<ComPackageDataReturn *>(package));
      break;

    case ComPackage::DataChanged:
      dataChanged(static_cast<ComPackageDataChanged *>(package));
      break;

    case ComPackage::DataSet:
      qCritical() << tr("ERROR: Received DataSet package!");
      break;

    case ComPackage::Reject: {
      _dataRequest.remove(static_cast<ComPackageReject *>(package)->originId());

      qDebug() << tr("WARNING: Package has been rejected!");

      QMessageBox msgBox;
      msgBox.setText("Request rejected by server.");
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.setIcon(QMessageBox::Warning);
      msgBox.exec();

      if (_tryLogin)
        onDisconnectFromServer();
    } break;

    default:
      qDebug() << tr("WARNING: Received unknown package!");
      break;
    }
  }
}

//------------------------------------------------------------------------------

void Executor::onWaiterCategoryAdd(int categoryId) {
  ComPackageCommand pc;
  pc.setCommandType(ComPackage::AddWaiterCategory);
  QJsonArray arr;
  arr.append(reinterpret_cast<Waiter *>(sender())->id());
  arr.append(categoryId);
  pc.setData(arr);

  if (!_tcp_client.send(pc)) {
    qCritical() << tr("FATAL: Could not send data set package!");

    QMessageBox msgBox;
    msgBox.setText("Network I/O-Error!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
  }
}

//------------------------------------------------------------------------------

void Executor::onWaiterCategoryRemove(int categoryId) {
  ComPackageCommand pc;
  pc.setCommandType(ComPackage::RemoveWaiterCategory);
  QJsonArray arr;
  arr.append(reinterpret_cast<Waiter *>(sender())->id());
  arr.append(categoryId);
  pc.setData(arr);

  if (!_tcp_client.send(pc)) {
    qCritical() << tr("FATAL: Could not send data set package!");

    QMessageBox msgBox;
    msgBox.setText("Network I/O-Error!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
  }
}

//------------------------------------------------------------------------------

void Executor::requestCategoryIds() {
  ComPackageDataRequest *request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestCategoryIds);

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestProductIds(int categoryId) {
  ComPackageDataRequest *request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestProductIds);
  request->setDataName(QString("%1").arg(categoryId));

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestCategory(int categoryId) {
  ComPackageDataRequest *request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestCategory);
  request->setDataName(QString("%1").arg(categoryId));

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestProduct(int productId) {
  ComPackageDataRequest *request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestProduct);
  request->setDataName(QString("%1").arg(productId));

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestUser(int userId) {
  ComPackageDataRequest *request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestUser);
  request->setDataName(QString("%1").arg(userId));

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestServerConfigs() {
  ComPackageDataRequest *request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestConfig);

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestAdvertising(int fileId) {
  ComPackageDataRequest *request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestMedia);
  request->setDataName(QString("%1").arg(fileId));

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestLicenceStatus() {
  //    ComPackageDataRequest* request = new ComPackageDataRequest();
  //    request->setDataCategory(ComPackage::RequestLicence);

  //    if (!_tcp_client.send(*request)) {
  //      qCritical() << tr("Could not send request!");
  //    } else {
  //      _dataRequest[request->id()] = request;
  //    }
}

//------------------------------------------------------------------------------

void Executor::requestClientIds() {
  ComPackageDataRequest *request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestUserIds);

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestMediaIds() {
  ComPackageDataRequest *request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestMediaIds);

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestAdvertisingConfigs() {
  ComPackageDataRequest *request = new ComPackageDataRequest();
  request->setDataCategory(ComPackage::RequestAdvertisingConfig);

  if (!_tcp_client.send(*request)) {
    qCritical() << tr("Could not send request!");
  } else {
    _dataRequest[request->id()] = request;
  }
}

//------------------------------------------------------------------------------

void Executor::requestSystemVersions(){
    ComPackageDataRequest *request = new ComPackageDataRequest();
    request->setDataCategory(ComPackage::RequestSystemVersions);

    if (!_tcp_client.send(*request)) {
      qCritical() << tr("Could not send request!");
    } else {
      _dataRequest[request->id()] = request;
    }
}

//------------------------------------------------------------------------------

void Executor::dataReturned(ComPackageDataReturn *package) {
  _dataRequest.remove(package->originId());

  switch (package->dataCategory()) {
  case ComPackage::RequestImage: {
    qCritical() << tr("The server request an imag from us!?!");
  } break;

  case ComPackage::RequestCategoryIds: {
    QJsonArray arr = package->data().toArray();
    foreach (QJsonValue val, arr) {
      int id = val.toInt();
      requestCategory(id);
    }
  } break;

  case ComPackage::RequestProductIds: {
    QJsonArray arr = package->data().toArray();
    foreach (QJsonValue val, arr) {
      int id = val.toInt();
      requestProduct(id);
    }
  } break;

  case ComPackage::RequestCategory: {
    ProductCategory *category = ProductCategory::fromJSON(package->data());
    requestProductIds(category->id());
    _products->addCategory(category);
  } break;

  case ComPackage::RequestProduct: {
    Product *product = Product::fromJSON(package->data());
    _products->addProduct(product);
  } break;

  case ComPackage::RequestConfig: {
    loadServerConfigs(package->data().toString());
  } break;
  case ComPackage::RequestLicence: {
    loadLicenceStatus(package->data().toString());
  } break;
  case ComPackage::RequestUserIds: {
    QJsonArray arr = package->data().toArray();
    foreach (QJsonValue val, arr) {
      int id = val.toInt();
      requestUser(id);
    }
  } break;
  case ComPackage::RequestUser: {
    User *user = reinterpret_cast<User *>(Client::fromJSON(package->data()));
    _users->addUser(user);
    if (user->accountType() == 0) {
      // Bind signal for add category and remove category from waiter
      connect(reinterpret_cast<Waiter *>(user), &Waiter::addNewCategory, this,
              &Executor::onWaiterCategoryAdd);
      connect(reinterpret_cast<Waiter *>(user), &Waiter::removeCategory, this,
              &Executor::onWaiterCategoryRemove);
    }
    // Bind name change
    connect(user, &Client::nameChanged, this, &Executor::onUpdateClient);
    // Bind client password change
    connect(user, &User::hashPasswordChanged, this,
            &Executor::onUpdateUserPassword);
  } break;
  case ComPackage::RequestMediaIds: {
    QJsonArray arr = package->data().toArray();
    foreach (QJsonValue val, arr) {
      int id = val.toInt();
      if(id>=0){    //If List is empty we get id=-1
      QString _id=QString::number(id);
      requestAdvertising(id);
      }
    }
  } break;
  case ComPackage::RequestMedia: {

      AdvertisingVideo *ad=NULL;
      File *file= File::fromJSON(package->data());
      switch (file->_fileInfo._type)
      {
      case ComPackage::AdvertisingVideo:
      {
          ad=reinterpret_cast <AdvertisingVideo*> (file);
          _files->addFile(ad);
      }break;

      case ComPackage::AdvertisingPicture:
      {

      }break;
      case ComPackage::CatergoryIcon:
      {

      }break;
      case ComPackage::ProductPicture:
      {

      }break;
      case ComPackage::ProductVideo:
      {

      }break;
      default : {qCritical() << "unknown package";} break;
      }
  }break;
  case ComPackage::RequestSystemVersions: {
      rotable::SystemUpdate *systemupdate= rotable::SystemUpdate::fromJSON(package->data());
      emit _mainwindow->setCurrentVersion(QString::number(systemupdate->getCurrentVersion()));
      emit _mainwindow->setAvailableVersion(QString::number(systemupdate->getAvailableVersion()));
      //qDebug()<<"es kommt hier an"<<qSetRealNumberPrecision(2)<< systemupdate->getCurrentVersion()<<" \n";
  }break;
  case ComPackage::RequestAdvertisingConfig: {
      int frequence= package->data().toInt();
      _dataBaseFrequnceAdvertising=frequence;
       emit _mainwindow->setFrequencePlayTime(frequence);
  }break;
  default: { qCritical() << tr("Unknown data package \"requestMedia\" returned"); } break;
  }

}

//------------------------------------------------------------------------------

void Executor::dataChanged(ComPackageDataChanged *package) {
  if (package) {
    switch (package->dataCategory()) {
    case ComPackage::RequestImage: {
    } break;
    case ComPackage::RequestCategoryIds: {
      _products->clear();
      requestCategoryIds();
    } break;
    case ComPackage::RequestProductIds: {
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
    case ComPackage::RequestCategory: {
      bool ok;
      int categoryId = package->dataName().toInt(&ok);
      if (!ok) {
        qCritical() << tr("Could not convert category id '%1' to int!")
                           .arg(package->dataName());
      } else {
        requestCategory(categoryId);
      }
    } break;
    case ComPackage::RequestProduct: {
      bool ok;
      int productId = package->dataName().toInt(&ok);
      if (!ok) {
        qCritical() << tr("Could not convert product id '%1' to int!")
                           .arg(package->dataName());
      } else {
        requestProduct(productId);
      }
    } break;
    case ComPackage::RequestUserIds: {
      _users->clear();
      requestClientIds();
    } break;
    case ComPackage::RequestMediaIds: {
      _files->clear();
      requestMediaIds();
    } break;
    case ComPackage::RequestAdvertisingConfig: {
      int frequence= package->dataName().toInt();
      _dataBaseFrequnceAdvertising=frequence;
      emit _mainwindow->setFrequencePlayTime(frequence);
    } break;
    default: {
      qCritical() << tr("Unknown data changed category '%1' received!")
                         .arg(package->dataCategory());
    } break;
    }
  }
}

//------------------------------------------------------------------------------

void Executor::loadServerConfigs(const QString &path) {
  emit onLicenceConfig(path);
}

//------------------------------------------------------------------------------

void Executor::loadLicenceStatus(const QString &status) {
  emit onLicenceStatus(status);
}

//------------------------------------------------------------------------------

void Executor::userSelectionChange() {
  if (!_users->getSelectedUser()) {
    emit setWaiterButton(false);
    emit setUserButtons(false);
    return;
  }
  emit setUserButtons(true);
  emit setWaiterButton(_users->getSelectedUser()->accountType() == 0 ? true
                                                                     : false);
}

//------------------------------------------------------------------------------

void Executor::SendProgressBarType(int value, int type)
{
    switch (type){
        case AddAdvertising:{
            _addNewVideo->progressBarChanged(value);
        }
    }
}

//------------------------------------------------------------------------------
