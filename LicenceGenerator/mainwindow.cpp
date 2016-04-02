#include "mainwindow.h"
#include "ui_mainwindow.h"

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
