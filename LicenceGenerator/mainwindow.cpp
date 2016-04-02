#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCryptographicHash>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    dataString = ui->hostNameLineEdit->text() + ";" + ui->platformComboBox->currentText() + ";" + QString::number(ui->tableCountSpinBox->value());

    QString hash = QTextCodec::codecForName("UTF-8")->toUnicode(QCryptographicHash::hash(dataString.toUtf8(), QCryptographicHash::Sha3_512).toHex());

    QString tmp = dataString + ";;" + hash;
    ui->plainTextEdit->setPlainText(tmp);
}
