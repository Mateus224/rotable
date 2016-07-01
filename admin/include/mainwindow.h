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
 void actionConnect();
 void actionDisconnect();
 void actionAddProductCategory();
 void actionAddProduct();
 void actionResetDatabase();
 void actionExportDatabase();
 void actionImportDatabase();
 void actionRemoveCurrentEntry();
 void actionRenameCurrentEntry();
 void actionExportStatistic();
 void actionStartDebugServerListening();
 void actionStopDebugServerListening();
 void actionClearDebugServerLog();
 void actionAddLicence();
 void actionSetLicencePath();
 void onLicencePathSet(QString);
 void onLicenceStatusSet(QString);
 void actionProductUp(QModelIndex);
 void actionProductDown(QModelIndex);
 void actionCategoryUp(QModelIndex);
 void actionCategoryDown(QModelIndex);


public slots:
 void onConnectionEstablished();
 void onConnectionLost();
 void onStatusBarTextChanged(QString text);
 void onServerLogConnectionEstablished();
 void onServerLogConnectionLost();
 void onServerLog(rotable::LogManager::LogMessage message);
 void onViewSelected(int id);
 void onUp();
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
 QString _serverDebugTabLabel;
}; // class MainWindow

//------------------------------------------------------------------------------
#endif // MAINWINDOW_H
