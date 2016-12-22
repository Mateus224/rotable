#include "include/dialog/systemupdatedialog.h"
#include "ui_systemupdatedialog.h"

SystemUpdateDialog::SystemUpdateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemUpdateDialog)
{
    ui->setupUi(this);
}

SystemUpdateDialog::~SystemUpdateDialog()
{
    delete ui;
}

void SystemUpdateDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QString compareSave= "&Yes";
    if(compareSave.compare(button->text())==0)
        QDialog::accept();
}
