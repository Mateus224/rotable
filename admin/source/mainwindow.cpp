#include "private/precomp.h"

#include "producttablemodel.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "producttableview.h"

//------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  _ui(new Ui::MainWindow), _isClosing(false)
{
  _ui->setupUi(this);
  _ui->_tabWidget->setEnabled(false);

  connect(_ui->_actionConnect, SIGNAL(triggered()),
          this, SIGNAL(actionConnect()));
  connect(_ui->_actionDisconnect, SIGNAL(triggered()),
          this, SIGNAL(actionDisconnect()));
  connect(_ui->_toolButtonAddCategory, SIGNAL(clicked(bool)),
          this, SIGNAL(actionAddProductCategory()));
  connect(_ui->_toolButtonAddProduct, SIGNAL(clicked(bool)),
          this, SIGNAL(actionAddProduct()));
  connect(_ui->_toolButtonDbReset, SIGNAL(clicked(bool)),
          this, SIGNAL(actionResetDatabase()));
  connect(_ui->_toolButtonDbExport, SIGNAL(clicked()),
          this, SIGNAL(actionExportDatabase()));
  connect(_ui->_toolButtonDbImport, SIGNAL(clicked()),
          this, SIGNAL(actionImportDatabase()));
  connect(_ui->_toolButtonRemove, SIGNAL(clicked(bool)),
          this, SIGNAL(actionRemoveCurrentEntry()));
  connect(_ui->_toolButtonRename, SIGNAL(clicked(bool)),
          this, SIGNAL(actionRenameCurrentEntry()));
  connect(_ui->_toolButtonExport, SIGNAL(clicked(bool)),
          this, SIGNAL(actionExportStatistic()));
  connect(_ui->_toolButtonClearDebugListening, SIGNAL(clicked()),
          this, SIGNAL(actionClearDebugServerLog()));
  connect(_ui->_toolButtonStartDebugListening, SIGNAL(clicked()),
          this, SIGNAL(actionStartDebugServerListening()));
  connect(_ui->_toolButtonStopDebugListening, SIGNAL(clicked()),
          this, SIGNAL(actionStopDebugServerListening()));
  connect(_ui->_toolAddLicence, &QPushButton::clicked,
          this, &MainWindow::actionAddLicence);
  connect(this, &MainWindow::onLicencePathSet,
          _ui->licencePathLineEdit, &QLineEdit::setText);
  connect(this, &MainWindow::onLicenceStatusSet,
          _ui->licenceStatusLineEdit, &QLineEdit::setText);
  connect(_ui->_tableViewProducts, SIGNAL(selectionChanged(int)), this, SLOT(onViewSelected(int)));
   connect(_ui->_listViewCategories, SIGNAL(selectionChanged(int)), this, SLOT(onViewSelected(int)));
  _ui->_statusBar->showMessage(tr("Disconnected"));
  connect(_ui->_toolButtonUp, &QToolButton::clicked, this, &MainWindow::onUp);
  connect(_ui->_toolButtonDown, &QToolButton::clicked, this, &MainWindow::onDown);
  connect(_ui->_toolButtonAddUser, &QToolButton::clicked, this,&MainWindow::actionAddUser);

  //_ui->d_plot->setMode(3);

  // Initially hide ServerDebug tab
  int serverDebugTabIdx = _ui->_tabWidget->indexOf(_ui->_tabServerDebug);
  Q_ASSERT(-1 != serverDebugTabIdx);
  _serverDebugTabIcon = _ui->_tabWidget->tabIcon(serverDebugTabIdx);
  _serverDebugTabLabel = _ui->_tabWidget->tabText(serverDebugTabIdx);
  _ui->_tabWidget->removeTab(serverDebugTabIdx);
  //Always run this same tab
  _ui->_tabWidget->setCurrentIndex(0);

}

//------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
  QSettings settings;
  settings.setValue("mainWindowGeometry", saveGeometry());
  settings.setValue("mainWindowState", saveState());
  settings.setValue("tabDatabaseSplitterGeometry", _ui->_splitterDb->saveGeometry());
  settings.setValue("tabDatabaseSplitterState", _ui->_splitterDb->saveState());
  settings.setValue("tableViewProductsGeometry", _ui->_tableViewProducts->saveGeometry());

  if (_ui->_tableViewProducts->horizontalHeader()->sectionSize(0) != 0) {
    settings.setValue("tableViewProductsGeometryColumnNameWidth",
                      _ui->_tableViewProducts->horizontalHeader()->sectionSize(ProductTableModel::name));
    settings.setValue("tableViewProductsGeometryColumnAmounWidth",
                      _ui->_tableViewProducts->horizontalHeader()->sectionSize(ProductTableModel::amount));
    settings.setValue("tableViewProductsGeometryColumnIconWidth",
                      _ui->_tableViewProducts->horizontalHeader()->sectionSize(ProductTableModel::icon));
    settings.setValue("tableViewProductsGeometryColumnPriceWidth",
                      _ui->_tableViewProducts->horizontalHeader()->sectionSize(ProductTableModel::price));
  }

  delete _ui;
}

//------------------------------------------------------------------------------

void MainWindow::exportPdf()
{
  //_ui->d_plot->exportPlot();
}

//------------------------------------------------------------------------------

void MainWindow::clearDebugServerLog()
{
  _ui->_textEditServerLog->clear();
}

//------------------------------------------------------------------------------

void MainWindow::restore()
{
  QSettings settings;
  restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
  restoreState(settings.value("mainWindowState").toByteArray());
  _ui->_splitterDb->restoreGeometry(settings.value("tabDatabaseSplitterGeometry").toByteArray());
  _ui->_splitterDb->restoreState(settings.value("tabDatabaseSplitterState").toByteArray());
  _ui->_tableViewProducts->restoreGeometry(settings.value("tableViewProductsGeometry").toByteArray());

  _ui->_tableViewProducts->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
  _ui->_tableViewProducts->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
  _ui->_tableViewProducts->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Interactive);

  _ui->_tableViewProducts->horizontalHeader()->resizeSection(
        ProductTableModel::name, settings.value("tableViewProductsGeometryColumnNameWidth", 150).toInt());
  _ui->_tableViewProducts->horizontalHeader()->resizeSection(
        ProductTableModel::amount, settings.value("tableViewProductsGeometryColumnAmountWidth", 75).toInt());
  _ui->_tableViewProducts->horizontalHeader()->resizeSection(
        ProductTableModel::icon, settings.value("tableViewProductsGeometryColumnIconWidth", 100).toInt());
  _ui->_tableViewProducts->horizontalHeader()->resizeSection(
        ProductTableModel::price, settings.value("tableViewProductsGeometryColumnPriceWidth", 100).toInt());
}

//------------------------------------------------------------------------------

void MainWindow::closeEvent(QCloseEvent *)
{
  _isClosing = true;
}

//------------------------------------------------------------------------------

void MainWindow::keyPressEvent(QKeyEvent* event)
{
  if(event->key() != Qt::Key_Alt
     && event->key() != Qt::Key_Control)
  {
    if(event->modifiers() & Qt::AltModifier
       && event->modifiers() & Qt::ControlModifier)
    {
      if (event->key() == Qt::Key_D) {
        if (-1 == _ui->_tabWidget->indexOf(_ui->_tabServerDebug)) {
          _ui->_tabWidget->addTab(_ui->_tabServerDebug, _serverDebugTabIcon,
                                  _serverDebugTabLabel);
        }
        _ui->_tabWidget->setCurrentWidget(_ui->_tabServerDebug);
      }
    }
  }
}

//------------------------------------------------------------------------------

void MainWindow::onConnectionEstablished()
{
  _ui->_actionConnect->setEnabled(false);
  _ui->_actionDisconnect->setEnabled(true);

  _ui->_tabWidget->setEnabled(true);
}

//------------------------------------------------------------------------------

void MainWindow::onConnectionLost()
{
  _ui->_actionConnect->setEnabled(true);
  _ui->_actionDisconnect->setEnabled(false);

  _ui->_tabWidget->setEnabled(false);
}

//------------------------------------------------------------------------------

void MainWindow::onStatusBarTextChanged(QString text)
{
  _ui->_statusBar->showMessage(text);
}

//------------------------------------------------------------------------------

void MainWindow::onServerLogConnectionEstablished()
{
  _ui->_toolButtonStartDebugListening->setEnabled(false);
  _ui->_toolButtonStopDebugListening->setEnabled(true);
  _ui->_toolButtonClearDebugListening->setEnabled(true);
  _ui->_textEditServerLog->clear();
}

//------------------------------------------------------------------------------

void MainWindow::onServerLogConnectionLost()
{
  _ui->_toolButtonStartDebugListening->setEnabled(true);
  _ui->_toolButtonStopDebugListening->setEnabled(false);
  _ui->_toolButtonClearDebugListening->setEnabled(false);
}

//------------------------------------------------------------------------------

void MainWindow::onServerLog(rotable::LogManager::LogMessage message)
{
  switch (message.level()) {
  case rotable::LogManager::error:
  {
    _ui->_textEditServerLog->setTextColor(Qt::darkRed);
  } break;
  case rotable::LogManager::warning:
  {
    _ui->_textEditServerLog->setTextColor(Qt::darkYellow);
  } break;
  case rotable::LogManager::qt:
  {
    _ui->_textEditServerLog->setTextColor(Qt::darkGreen);
  } break;
  case rotable::LogManager::json:
  {
    _ui->_textEditServerLog->setTextColor(Qt::darkCyan);
  } break;
  default:
  case rotable::LogManager::info:
  {
    _ui->_textEditServerLog->setTextColor(Qt::black);
  } break;
  }

  _ui->_textEditServerLog->append(message.message());
}

void MainWindow::onViewSelected(int id)
{
    Q_UNUSED(id);
    bool state = false;
    auto model1 = _ui->_listViewCategories->selectionModel();
    if(model1)
        state |= model1->hasSelection();
    auto model2 = _ui->_tableViewProducts->selectionModel();
    if(model2)
        state |= model2->hasSelection();
    _ui->_toolButtonUp->setEnabled(state);
    _ui->_toolButtonDown->setEnabled(state);
}

void MainWindow::onUp()
{
    //First we check if we select prodct (when product is selected also category is selected)
    if(_ui->_tableViewProducts->selectionModel()->hasSelection())
    {
        emit actionProductUp();
        return;
    }
    if(_ui->_listViewCategories->selectionModel()->hasSelection())
    {
        emit actionCategoryUp();
        return;
    }
}

void MainWindow::onDown()
{
    //First we check if we select prodct (when product is selected also category is selected)
    if(_ui->_tableViewProducts->selectionModel()->hasSelection())
    {
        emit actionProductDown();
        return;
    }
    if(_ui->_listViewCategories->selectionModel()->hasSelection())
    {
        emit actionCategoryDown();
        return;
    }
}
