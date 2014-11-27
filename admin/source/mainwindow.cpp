#include "private/precomp.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

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

  _ui->_statusBar->showMessage(tr("Disconnected"));

  _ui->d_plot->setMode(3);

  // Initially hide ServerDebug tab
  int serverDebugTabIdx = _ui->_tabWidget->indexOf(_ui->_tabServerDebug);
  Q_ASSERT(-1 != serverDebugTabIdx);
  _serverDebugTabIcon = _ui->_tabWidget->tabIcon(serverDebugTabIdx);
  _serverDebugTabLabel = _ui->_tabWidget->tabText(serverDebugTabIdx);
  _ui->_tabWidget->removeTab(serverDebugTabIdx);
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
    settings.setValue("tableViewProductsGeometryColumn0Width", _ui->_tableViewProducts->horizontalHeader()->sectionSize(0));
    settings.setValue("tableViewProductsGeometryColumn1Width", _ui->_tableViewProducts->horizontalHeader()->sectionSize(1));
    settings.setValue("tableViewProductsGeometryColumn2Width", _ui->_tableViewProducts->horizontalHeader()->sectionSize(2));
    settings.setValue("tableViewProductsGeometryColumn3Width", _ui->_tableViewProducts->horizontalHeader()->sectionSize(3));
  }

  delete _ui;
}

//------------------------------------------------------------------------------

void MainWindow::exportPdf()
{
  _ui->d_plot->exportPlot();
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

  _ui->_tableViewProducts->horizontalHeader()->resizeSection(0, settings.value("tableViewProductsGeometryColumn0Width", 200).toInt());
  _ui->_tableViewProducts->horizontalHeader()->resizeSection(1, settings.value("tableViewProductsGeometryColumn1Width", 150).toInt());
  _ui->_tableViewProducts->horizontalHeader()->resizeSection(2, settings.value("tableViewProductsGeometryColumn2Width", 200).toInt());
  _ui->_tableViewProducts->horizontalHeader()->resizeSection(3, settings.value("tableViewProductsGeometryColumn3Width").toInt());
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
