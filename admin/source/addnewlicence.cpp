#include "private/precomp.h"

#include "addnewlicence.h"

#include <QFileDialog>

AddNewLicence::AddNewLicence(QWidget *parent) : QDialog(parent), _ui(new Ui::Dialog)
{
      _ui->setupUi(this);
}

AddNewLicence::~AddNewLicence()
{

}

void AddNewLicence::on_addLicenceButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select licence"), "~", tr("Licence file (*.lic)"));

    if(fileName != "")
    {
        _licence = fileName;
        _ui->addLicenceSignButton->setEnabled(true);
    }
}

void AddNewLicence::on_addLicenceSignButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select licence"), "~", tr("Licence file (*.lic)"));

    _sign = fileName;
}
