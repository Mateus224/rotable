#include "resetpassword.h"
#include "ui_resetpassword.h"
#include <QMessageBox>

ResetPassword::ResetPassword(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ResetPassword)
{
  ui->setupUi(this);
  ui->_passswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
  ui->_passwordLineEdit2->setEchoMode(QLineEdit::EchoMode::Password);
}

ResetPassword::~ResetPassword()
{
  delete ui;
}

QString ResetPassword::password() const
{
  return _password;
}

void ResetPassword::accept()
{
  if(ui->_passswordLineEdit->text() == ui->_passwordLineEdit2->text())
  {
    _password = ui->_passswordLineEdit->text();
    QDialog::accept();
  }
  else
  {
    QMessageBox msgBox;
    msgBox.setText(tr("Password doesn't match"));
    msgBox.exec();
  }
}
