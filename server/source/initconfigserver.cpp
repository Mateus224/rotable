#include "include/initconfigserver.h"
#include "ui_initconfigserver.h"

InitConfigServer::InitConfigServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InitConfigServer)
{
    ui->setupUi(this);
}

InitConfigServer::~InitConfigServer()
{
    delete ui;
}

void InitConfigServer::on_pushButton_clicked()
{
    //TODO: add verification values
    //TODO: save values
}

void InitConfigServer::on_pushButton_2_clicked()
{
    ui->dbhost->setText("localhost");
    ui->dbprefix->setText("rotable_");
    ui->dbuser->setText("rotable");
    ui->dbpass->setText("rotable");
    ui->netport->setValue(5000);
}
