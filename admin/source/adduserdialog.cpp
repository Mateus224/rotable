#include "adduserdialog.h"
#include "ui_adduserdialog.h"

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adduserdialog)
{
    ui->setupUi(this);
    ui->_lineEditPassword->setEchoMode(QLineEdit::EchoMode::Password);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::on_buttonBox_accepted()
{
  _name = ui->_lineEditLogin->text();
  _password = ui->_lineEditPassword->text();
  _accountType = ui->_comboBoxAccountType->currentText() == "Waiter" ? 0 : 1;
}

int AddUserDialog::accountType() const
{
    return _accountType;
}

QString AddUserDialog::name() const
{
    return _name;
}

QString AddUserDialog::password() const
{
    return _password;
}
