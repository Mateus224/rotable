#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//------------------------------------------------------------------------------

#ifndef QDYNAMICMAINWINDOW_H
#include <QMainWindow>
#endif

#include "logmanager.h"

//------------------------------------------------------------------------------

namespace Ui {
 class MainWindow;
}

//------------------------------------------------------------------------------

/**
 * MainWindow
 */
class MainWindow : public QMainWindow
{
 Q_OBJECT

 friend class Controller;

public:
 /**
 * Contructor.
 *
 * @param parent parent object
 */
 explicit MainWindow(QWidget* parent = 0);

 /**
 * Destructor
 */
 ~MainWindow();

 /**
 * Check whether the main window is currently closing.
 *
 * @return true if window is closing
 */
 inline bool isClosing() const { return _isClosing; }

 /**
 * Call the export function in statistic view.
 */
 void exportPdf();

 /**
 * Clear all debug server log messages
 */
 void clearDebugServerLog();

 /**
 * Restore saved geometry and states of widgets.
 */
 void restore();

signals:
 /**
  * @brief
  *
  */
 void actionConnect();
 /**
  * @brief
  *
  */
 void actionDisconnect();
 /**
  * @brief
  *
  */
 void actionAddProductCategory();
 /**
  * @brief
  *
  */
 void actionAddProduct();
 /**
  * @brief
  *
  */
 void actionResetDatabase();
 /**
  * @brief
  *
  */
 void actionExportDatabase();
 /**
  * @brief
  *
  */
 void actionImportDatabase();
 /**
  * @brief
  *
  */
 void actionRemoveCurrentEntry();
 /**
  * @brief
  *
  */
 void actionRenameCurrentEntry();
 /**
  * @brief
  *
  */
 void actionExportStatistic();
 /**
  * @brief
  *
  */
 void actionStartDebugServerListening();
 /**
  * @brief
  *
  */
 void actionStopDebugServerListening();
 /**
  * @brief
  *
  */
 void actionClearDebugServerLog();
 /**
  * @brief
  *
  */
 void actionAddLicence();
 /**
  * @brief
  *
  */
 void actionSetLicencePath();
 /**
  * @brief
  *
  * @param QString
  */
 void onLicencePathSet(QString);
 /**
  * @brief
  *
  * @param QString
  */
 void onLicenceStatusSet(QString);
 /**
  * @brief
  *
  */
 void actionProductUp();
 /**
  * @brief
  *
  */
 void actionProductDown();
 /**
  * @brief
  *
  */
 void actionCategoryUp();
 /**
  * @brief
  *
  */
 void actionCategoryDown();

 /**
  * @brief Open new dialog for add user
  * @related Executor::onAddUser
  */
 void actionAddUser();


public slots:
 /**
  * @brief
  *
  */
 void onConnectionEstablished();
 /**
  * @brief
  *
  */
 void onConnectionLost();
 /**
  * @brief
  *
  * @param text
  */
 void onStatusBarTextChanged(QString text);
 /**
  * @brief
  *
  */
 void onServerLogConnectionEstablished();
 /**
  * @brief
  *
  */
 void onServerLogConnectionLost();
 /**
  * @brief
  *
  * @param message
  */
 void onServerLog(rotable::LogManager::LogMessage message);
 /**
  * @brief
  *
  * @param id
  */
 void onViewSelected(int id);
 /**
  * @brief
  *
  */
 void onUp();
 /**
  * @brief
  *
  */
 void onDown();

protected:
 /**
 * This event is called, when the user wants to close the main window.
 *
 * @param event event
 */
 void closeEvent(QCloseEvent *event);

 /**
 * A key has been pressed.
 *
 * @param event event
 */
 void keyPressEvent(QKeyEvent *event);

private:
 /* UI */
 Ui::MainWindow* _ui;

 /* Whether the application is currently shutting down. */
 bool _isClosing;

 QIcon _serverDebugTabIcon;
 QString _serverDebugTabLabel; /**< TODO: describe */
}; // class MainWindow

//------------------------------------------------------------------------------
#endif // MAINWINDOW_H
