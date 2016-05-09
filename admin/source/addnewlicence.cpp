#include "private/precomp.h"

#include "addnewlicence.h"

#include <QFileDialog>

AddNewLicence::AddNewLicence(QWidget *parent) : QDialog(parent), _ui(new Ui::Dialog)
{
      _ui->setupUi(this);
      _ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
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

    if(fileName != "")
    {
        _sign = fileName;
        _ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    }

}
