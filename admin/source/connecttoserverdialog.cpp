#include "private/precomp.h"

#include "connecttoserverdialog.h"
#include "ui_connectToServer.h"

//------------------------------------------------------------------------------

ConnectToServerDialog::ConnectToServerDialog(QWidget *parent, Qt::WindowFlags f)
  : QDialog(parent, f), _ui(new Ui::ConnectToServerDialog)
{
  _ui->setupUi(this);
}

//------------------------------------------------------------------------------

void ConnectToServerDialog::setServerAddress(const QString &address)
{
  _ui->_lineEditServerAddress->setText(address);
}

//------------------------------------------------------------------------------

void ConnectToServerDialog::setServerPort(int port)
{
  _ui->_lineEditServerPort->setText(QString("%1").arg(port));
}

//------------------------------------------------------------------------------

void ConnectToServerDialog::setUsername(const QString &username)
{
  _ui->_lineEditUser->setText(username);
}

//------------------------------------------------------------------------------

QString ConnectToServerDialog::serverAddress() const
{
  return _ui->_lineEditServerAddress->text();
}

//------------------------------------------------------------------------------

int ConnectToServerDialog::serverPort() const
{
  return _ui->_lineEditServerPort->text().toInt();
}

//------------------------------------------------------------------------------

QString ConnectToServerDialog::username() const
{
  return _ui->_lineEditUser->text();
}

//------------------------------------------------------------------------------

QString ConnectToServerDialog::password() const
{
  return _ui->_lineEditPassword->text();
}
