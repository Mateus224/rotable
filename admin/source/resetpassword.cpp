#include "resetpassword.h"
#include "ui_resetpassword.h"

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

}
