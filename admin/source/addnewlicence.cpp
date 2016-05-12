#include "private/precomp.h"

#include "addnewlicence.h"

#include <QFileDialog>
#include <QCryptographicHash>
#include <QTextCodec>

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
        tr("Select licence"), "~", tr("Licence file (*.dat)"));

    if(fileName != "")
    {
        QFile f(fileName);
        if (!f.open(QFile::ReadOnly | QFile::Text))
            //TODO: show error message
            return;
        QTextStream in(&f);
        if(!checkLicenceHash(in.readAll()))
            //TODO: show error message
            return;

        _licence = fileName;
        _ui->addLicenceSignButton->setEnabled(true);
    }
}

void AddNewLicence::on_addLicenceSignButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select licence"), "~", tr("Signed file (*.dat)"));

    if(fileName != "")
    {
        _sign = fileName;
        _ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    }

}

bool AddNewLicence::checkLicenceHash(QString licence)
{
    QStringList splitLicence = licence.split(";;");
    return splitLicence[1] != QTextCodec::codecForName("UTF-8")->toUnicode(
                    QCryptographicHash::hash(splitLicence[0].toUtf8(),
                    QCryptographicHash::Sha3_512).toHex());
}
