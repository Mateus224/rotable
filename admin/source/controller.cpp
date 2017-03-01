#include "private/precomp.h"
#include "tcpclient.h"

#include "categorylistmodel.h"
#include "controller.h"
#include "mainwindow.h"
#include "producttablemodel.h"
#include "ui_mainwindow.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

Controller::Controller(MainWindow *mainwindow, const QString &configFilePath)
    : QObject(0), _mainwindow(mainwindow),
      _executor(mainwindow, configFilePath), _users(), _files(),_advertisingTableView() {
  _executor.setImageContainer(&_images);
  _executor.setProductContainer(&_products);
  _executor.setUserContainer(&_users);
  _executor.setFileContainer(&_files);

  _categoryListModel = new CategoryListModel(this);
  _categoryListModel->setProductContainer(&_products);
  _categoryListModel->setImageContainer(&_images);
  _executor.setCategoryTableModel(_categoryListModel);

  _mainwindow->_ui->_listViewCategories->setModel(_categoryListModel);
  _executor.setTableViewCategory(_mainwindow->_ui->_listViewCategories);

  _productTableModel = new ProductTableModel(this);
  _productTableModel->setProductContainer(&_products);
  _productTableModel->setImageContainer(&_images);

  _executor.setProductTableModel(_productTableModel);

  _mainwindow->_ui->_tableViewProducts->setModel(_productTableModel);
  _executor.setTableViewProducts(_mainwindow->_ui->_tableViewProducts);

  _userTableModel = new UserTableModel();
  _userTableModel->setUserContainer(&_users);

  _mainwindow->_ui->_userTableView->setModel(
      reinterpret_cast<QAbstractItemModel *>(_userTableModel));

  _advertisingTableModel=new AdvertisingTableModel();
  _advertisingTableModel->setFileContainer(&_files);

  _mainwindow->_ui->_advertisingTableView->setModel(
      reinterpret_cast<QAbstractItemModel*>(_advertisingTableModel));

  _mainwindow->restore();

  connect_signals();
}

//------------------------------------------------------------------------------

void Controller::connect_signals() {

  connect(&_executor, SIGNAL(connectionEstablished()), _mainwindow,
          SLOT(onConnectionEstablished()));

  connect(&_executor, SIGNAL(connectionLost()), _mainwindow,
          SLOT(onConnectionLost()));

  connect(_mainwindow, SIGNAL(actionConnect()), &_executor,
          SLOT(onConnectToServer()));

  connect(_mainwindow, SIGNAL(actionDisconnect()), &_executor,
          SLOT(onDisconnectFromServer()));

  connect(_mainwindow, SIGNAL(actionAddProductCategory()), &_executor,
          SLOT(onAddProductCategory()));

  connect(_mainwindow, SIGNAL(actionAddProduct()), &_executor,
          SLOT(onAddProduct()));

  connect(_mainwindow, SIGNAL(actionResetDatabase()), &_executor,
          SLOT(onResetDatabase()));

  connect(_mainwindow, SIGNAL(actionExportDatabase()), &_executor,
          SLOT(onExportDatabase()));

  connect(_mainwindow, SIGNAL(actionImportDatabase()), &_executor,
          SLOT(onImportDatabase()));

  connect(_mainwindow, SIGNAL(actionResetDatabase()), &_executor,
          SLOT(onResetDatabase()));

  connect(_mainwindow, SIGNAL(actionRemoveCurrentEntry()), &_executor,
          SLOT(onRemoveCurrentEntry()));

  connect(_mainwindow, SIGNAL(actionRenameCurrentEntry()), &_executor,
          SLOT(onRenameCurrentEntry()));

  connect(_mainwindow, SIGNAL(actionExportStatistic()), &_executor,
          SLOT(onExportStatistic()));

  connect(_mainwindow, SIGNAL(actionClearDebugServerLog()), &_executor,
          SLOT(onClearDebugServerLog()));

  connect(_mainwindow, SIGNAL(actionStartDebugServerListening()), &_executor,
          SLOT(onStartDebugServerListening()));

  connect(_mainwindow, SIGNAL(actionStopDebugServerListening()), &_executor,
          SLOT(onStopDebugServerListening()));

  connect(&_executor, SIGNAL(statusMessage(QString)), _mainwindow,
          SLOT(onStatusBarTextChanged(QString)));

  connect(&_executor, SIGNAL(serverLogConnectionEstablished()), _mainwindow,
          SLOT(onServerLogConnectionEstablished()));

  connect(&_executor, SIGNAL(serverLogConnectionLost()), _mainwindow,
          SLOT(onServerLogConnectionLost()));

  connect(&_executor, SIGNAL(serverLog(rotable::LogManager::LogMessage)),
          _mainwindow, SLOT(onServerLog(rotable::LogManager::LogMessage)));

  connect(&_executor, &Executor::setWaiterButton,
          _mainwindow, &MainWindow::setWaiterButtonStatus);

  connect(&_executor, &Executor::setUserButtons,
          _mainwindow, &MainWindow::setUserButtons);

  connect(_mainwindow->_ui->_userTableView->selectionModel(),
     SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
     &_executor, SLOT(handleSelectionChanged(QItemSelection)));

  //----------------------------------------------------------------------------

  connect(&_products, SIGNAL(categoryAdded(int)), _categoryListModel,
          SLOT(onCategoryAdded(int)));

  connect(&_products, SIGNAL(categoryRemoved(rotable::ProductCategory *)),
          _categoryListModel,
          SLOT(onCategoryRemoved(rotable::ProductCategory *)));

  connect(&_products, SIGNAL(categoryUpdated(rotable::ProductCategory *)),
          _categoryListModel,
          SLOT(onCategoryUpdated(rotable::ProductCategory *)));

  connect(&_products, SIGNAL(categoryUpdated(rotable::ProductCategory *)),
          &_executor, SLOT(onUpdateCategory(rotable::ProductCategory *)));

  connect(_mainwindow->_ui->_listViewCategories, SIGNAL(selectionChanged(int)),
          &_executor, SLOT(onCategorySelectionChanged(int)));

  connect(_mainwindow, &MainWindow::actionAddLicence, &_executor,
          &Executor::onAddLicence);

  connect(_mainwindow, &MainWindow::actionAddUser, &_executor,
          &Executor::onAddUser);

  connect(_mainwindow, &MainWindow::actionWaiterCategories, &_executor, &Executor::onWaiterCategoriesChange);

  connect(&_executor, &Executor::onLicenceConfig, _mainwindow,
          &MainWindow::onLicencePathSet);

  connect(&_executor, &Executor::onLicenceStatus, _mainwindow,
          &MainWindow::onLicenceStatusSet);

  connect(_mainwindow, &MainWindow::updateSystem,
          &_executor, &Executor::onUpdateSystem);

  connect(_mainwindow, &MainWindow::addVideo,
          &_executor, &Executor::onAddAdvertisingVideo);

  connect(_mainwindow, &MainWindow::removeVideo,
          &_executor, &Executor::onRemoveAdvertisingVideo);
  //----------------------------------------------------------------------------

  connect(_mainwindow, &MainWindow::actionProductUp, &_executor,
          &Executor::onProductUp);
  connect(_mainwindow, &MainWindow::actionProductDown, &_executor,
          &Executor::onProductDown);
  connect(_mainwindow, &MainWindow::actionCategoryUp, &_executor,
          &Executor::onCategoryUp);
  connect(_mainwindow, &MainWindow::actionCategoryDown, &_executor,
          &Executor::onCategoryDown);

  //----------------------------------------------------------------------------

  connect(&_products, SIGNAL(productAdded(int)), _productTableModel,
          SLOT(onProductAdded(int)));

  connect(&_products, SIGNAL(productRemoved(rotable::Product *)),
          _productTableModel, SLOT(onProductRemoved(rotable::Product *)));

  connect(&_products, SIGNAL(productUpdated(rotable::Product *)),
          _productTableModel, SLOT(onProductUpdated(rotable::Product *)));

  connect(&_products, SIGNAL(productUpdated(rotable::Product *)), &_executor,
          SLOT(onUpdateProduct(rotable::Product *)));

  //connect(&_files, SIGNAL(advertisingVideoUpdated(rotable::AdvertisingVideo *)),
  //        _advertisingTableModel, SLOT(updateModel())); crashes sometimes let commented

  connect(&_files, SIGNAL(advertisingVideoUpdated(rotable::AdvertisingVideo  *)), &_executor,
          SLOT(onUpdateAdvertisingVideo(rotable::AdvertisingVideo *)));

  connect(_mainwindow->_ui->_listViewCategories, SIGNAL(selectionChanged(int)),
          _productTableModel, SLOT(onCategoryChanged(int)));

  connect(_mainwindow->_ui->_tableViewProducts, SIGNAL(selectionChanged(int)),
          &_executor, SLOT(onProductSelectionChanged(int)));

  connect(_mainwindow->_ui->_advertisingTableView->selectionModel(),
    SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
    &_advertisingTableView, SLOT(selectionChanged(const QItemSelection &, const QItemSelection &)));
  connect(&_advertisingTableView, SIGNAL(selectionChanged(int)),
          &_executor, SLOT(onAdvertisingVideoSelectionChanged(int)));

  connect(_mainwindow, &MainWindow::actionChangeUserPassword,
          &_executor, &Executor::onChangePassword);

  connect(_mainwindow,&MainWindow::getFrequencePlayTime,
          &_executor, &Executor::onUpdateFrequencePlayTime);

  //----------------------------------------------------------------------------

  connect(&_users, &UserContainter::updateView, _userTableModel,
          &UserTableModel::updateModel);
  //----------------------------------------------------------------------------

  connect(&_files, &AdvertisingContainer::updateView, _advertisingTableModel,
          &AdvertisingTableModel::updateModel);

}
