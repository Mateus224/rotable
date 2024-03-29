#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCryptographicHash>
#include <QTextCodec>
#include <QFileDialog>
#include <QFileInfo>

#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
#include <string>

using namespace CryptoPP;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->licenceBeginDateEdit->setDate(QDate::currentDate());
    ui->licenceBeginDateEdit->setDateRange(QDate::currentDate(), QDate::currentDate().addYears(2));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_hostNameLineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->pushButton->setEnabled(ui->hostNameLineEdit->text().trimmed().length() != 0);
}

void MainWindow::on_pushButton_clicked()
{
    QString dataString;
    dataString = ui->hostNameLineEdit->text() + ";" + ui->platformComboBox->currentText() + ";" + QString::number(ui->tableCountSpinBox->value())
            + ";" + ui->licenceBeginDateEdit->date().toString("dd.MM.yyyy") + ";" + ui->licenceEndDateEdit->date().toString("dd.MM.yyyy");
    QString hash = QTextCodec::codecForName("UTF-8")->toUnicode(QCryptographicHash::hash(dataString.toUtf8(), QCryptographicHash::Sha3_512).toHex());
    QString tmp = dataString + ";;" + hash;


    string plain = tmp.toStdString();

    ui->plainTextEdit->setPlainText(plain.c_str());
}

void MainWindow::setLicenceDateEditValues(const QDate &date)
{
    if(date > ui->licenceEndDateEdit->date())
        ui->licenceEndDateEdit->setDate(date.addDays(1));
    ui->licenceEndDateEdit->setDateRange(date.addDays(1), date.addYears(1));
}

void MainWindow::on_plainTextEdit_textChanged()
{
    ui->pushButton_2->setEnabled((ui->plainTextEdit->toPlainText() != QString("")));
}

void MainWindow::on_pushButton_2_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("Select private key"), QDir().dirName(), tr("Key files (*.txt)"));

    string licence = ui->plainTextEdit->toPlainText().toStdString();

    AutoSeededRandomPool rng;

    CryptoPP::ByteQueue bytes;
    FileSource file(fileName.toStdString().c_str(), true, new Base64Decoder);
    file.TransferTo(bytes);
    bytes.MessageEnd();
    RSA::PrivateKey privateKey;
    privateKey.Load(bytes);

    RSASSA_PKCS1v15_SHA_Signer privkey(privateKey);
    SecByteBlock sbbSignature(privkey.SignatureLength());
    privkey.SignMessage(
        rng,
        (byte const*) licence.data(),
        licence.size(),
        sbbSignature);

    auto dirPath = QFileDialog::getExistingDirectory(this, tr("Select directory for save licence and sig"), QDir().dirName());

    FileSink sink(QDir(dirPath).filePath("licence.dat").toStdString().c_str());
    sink.Put((byte const*) licence.data(), licence.size());
    FileSink sinksig(QDir(dirPath).filePath("sig.dat").toStdString().c_str());
    sinksig.Put(sbbSignature, sbbSignature.size());
}
