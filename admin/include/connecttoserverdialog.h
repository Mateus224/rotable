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
  /**
   * @brief
   *
   * @param port
   */
  void setServerPort(int port);
  /**
   * @brief
   *
   * @param username
   */
  void setUsername(const QString& username);

  /**
   * @brief
   *
   * @return QString
   */
  QString serverAddress() const;
  /**
   * @brief
   *
   * @return int
   */
  int serverPort() const;
  /**
   * @brief
   *
   * @return QString
   */
  QString username() const;
  /**
   * @brief
   *
   * @return QString
   */
  QString password() const;

private:
  /* UI */
  Ui::ConnectToServerDialog* _ui;
}; // class ConnectToServerDialog

//------------------------------------------------------------------------------

#endif // CONNECTTOSERVERDIALOG_H
