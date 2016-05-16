#include "private/precomp.h"

#include "controller.h"
#include "mainwindow.h"
#include "categorylistmodel.h"
#include "producttablemodel.h"
#include "ui_mainwindow.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

Controller::Controller(MainWindow* mainwindow, const QString& configFilePath) :
  QObject(0), _mainwindow(mainwindow), _executor(mainwindow, configFilePath)
{
  _executor.setImageContainer(&_images);
  _executor.setProductContainer(&_products);

  _categoryListModel = new CategoryListModel(this);
  _categoryListModel->setProductContainer(&_products);
  _categoryListModel->setImageContainer(&_images);

  _mainwindow->_ui->_listViewCategories->setModel(_categoryListModel);

  _productTableModel = new ProductTableModel(this);
  _productTableModel->setProductContainer(&_products);
  _productTableModel->setImageContainer(&_images);

  _mainwindow->_ui->_tableViewProducts->setModel(_productTableModel);

  _mainwindow->restore();

  connect_signals();
}

//------------------------------------------------------------------------------

void Controller::connect_signals()
{
  connect(&_executor, SIGNAL(connectionEstablished()),
          _mainwindow, SLOT(onConnectionEstablished()));

  connect(&_executor, SIGNAL(connectionLost()),
          _mainwindow, SLOT(onConnectionLost()));

  connect(_mainwindow, SIGNAL(actionConnect()),
          &_executor, SLOT(onConnectToServer()));

  connect(_mainwindow, SIGNAL(actionDisconnect()),
          &_executor, SLOT(onDisconnectFromServer()));

  connect(_mainwindow, SIGNAL(actionAddProductCategory()),
          &_executor, SLOT(onAddProductCategory()));

  connect(_mainwindow, SIGNAL(actionAddProduct()),
          &_executor, SLOT(onAddProduct()));

  connect(_mainwindow, SIGNAL(actionResetDatabase()),
          &_executor, SLOT(onResetDatabase()));

  connect(_mainwindow, SIGNAL(actionExportDatabase()),
          &_executor, SLOT(onExportDatabase()));

  connect(_mainwindow, SIGNAL(actionImportDatabase()),
          &_executor, SLOT(onImportDatabase()));

  connect(_mainwindow, SIGNAL(actionResetDatabase()),
          &_executor, SLOT(onResetDatabase()));

  connect(_mainwindow, SIGNAL(actionRemoveCurrentEntry()),
          &_executor, SLOT(onRemoveCurrentEntry()));

  connect(_mainwindow, SIGNAL(actionRenameCurrentEntry()),
          &_executor, SLOT(onRenameCurrentEntry()));

  connect(_mainwindow, SIGNAL(actionExportStatistic()),
          &_executor, SLOT(onExportStatistic()));

  connect(_mainwindow, SIGNAL(actionClearDebugServerLog()),
          &_executor, SLOT(onClearDebugServerLog()));

  connect(_mainwindow, SIGNAL(actionStartDebugServerListening()),
          &_executor, SLOT(onStartDebugServerListening()));

  connect(_mainwindow, SIGNAL(actionStopDebugServerListening()),
          &_executor, SLOT(onStopDebugServerListening()));

  connect(&_executor, SIGNAL(statusMessage(QString)),
          _mainwindow, SLOT(onStatusBarTextChanged(QString)));

  connect(&_executor, SIGNAL(serverLogConnectionEstablished()),
          _mainwindow, SLOT(onServerLogConnectionEstablished()));

  connect(&_executor, SIGNAL(serverLogConnectionLost()),
          _mainwindow, SLOT(onServerLogConnectionLost()));

  connect(&_executor, SIGNAL(serverLog(rotable::LogManager::LogMessage)),
          _mainwindow, SLOT(onServerLog(rotable::LogManager::LogMessage)));

  //----------------------------------------------------------------------------

  connect(&_products, SIGNAL(categoryAdded(int)),
          _categoryListModel, SLOT(onCategoryAdded(int)));

  connect(&_products, SIGNAL(categoryRemoved(rotable::ProductCategory*)),
          _categoryListModel, SLOT(onCategoryRemoved(rotable::ProductCategory*)));

  connect(&_products, SIGNAL(categoryUpdated(rotable::ProductCategory*)),
          _categoryListModel, SLOT(onCategoryUpdated(rotable::ProductCategory*)));

  connect(&_products, SIGNAL(categoryUpdated(rotable::ProductCategory*)),
          &_executor, SLOT(onUpdateCategory(rotable::ProductCategory*)));

  connect(_mainwindow->_ui->_listViewCategories, SIGNAL(selectionChanged(int)),
          &_executor, SLOT(onCategorySelectionChanged(int)));

  connect(_mainwindow, &MainWindow::actionAddLicence,
          &_executor, &Executor::onAddLicence);

  connect(&_executor, &Executor::onLicenceConfig,
          _mainwindow, &MainWindow::onLicencePathSet);

  connect(&_executor, &Executor::onLicenceStatus,
          _mainwindow, &MainWindow::onLicenceStatusSet);

  //----------------------------------------------------------------------------

  connect(&_products, SIGNAL(productAdded(int)),
          _productTableModel, SLOT(onProductAdded(int)));

  connect(&_products, SIGNAL(productRemoved(rotable::Product*)),
          _productTableModel, SLOT(onProductRemoved(rotable::Product*)));

  connect(&_products, SIGNAL(productUpdated(rotable::Product*)),
          _productTableModel, SLOT(onProductUpdated(rotable::Product*)));

  connect(&_products, SIGNAL(productUpdated(rotable::Product*)),
          &_executor, SLOT(onUpdateProduct(rotable::Product*)));

  connect(_mainwindow->_ui->_listViewCategories, SIGNAL(selectionChanged(int)),
          _productTableModel, SLOT(onCategoryChanged(int)));

  connect(_mainwindow->_ui->_tableViewProducts, SIGNAL(selectionChanged(int)),
          &_executor, SLOT(onProductSelectionChanged(int)));
}
