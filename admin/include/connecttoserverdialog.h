#ifndef CONNECTTOSERVERDIALOG_H
#define CONNECTTOSERVERDIALOG_H

//------------------------------------------------------------------------------

#include <QDialog>

//------------------------------------------------------------------------------

namespace Ui {
  class ConnectToServerDialog;
}

//------------------------------------------------------------------------------

/**
 * This dialog asks the user to enter connection details as hostname, port,
 * username and password.
 */
class ConnectToServerDialog : public QDialog
{
  Q_OBJECT

public:
  /**
   * Constructor
   *
   * @param parent      parent widget
   * @param f           window flags
   */
  ConnectToServerDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);

  void setServerAddress(const QString& address);
  void setServerPort(int port);
  void setUsername(const QString& username);

  QString serverAddress() const;
  int serverPort() const;
  QString username() const;
  QString password() const;

private:
  /* UI */
  Ui::ConnectToServerDialog* _ui;
}; // class ConnectToServerDialog

//------------------------------------------------------------------------------

#endif // CONNECTTOSERVERDIALOG_H
