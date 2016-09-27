#include "resetpassword.h"
#include "ui_resetpassword.h"
#include <QMessageBox>

ResetPassword::ResetPassword(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ResetPassword)
{
  ui->setupUi(this);
}

ResetPassword::~ResetPassword()
{
  delete ui;
}

void ResetPassword::accept()
{
  if(ui->_passswordLineEdit->text() == ui->_passwordLineEdit2->text())
  {
    QDialog::accept();
  }
  else
  {
    QMessageBox msgBox;
    msgBox.setText(tr("Password doesn't match"));
    msgBox.exec();
  }
}
