#include "include/initconfigserver.h"
#include "ui_initconfigserver.h"

InitConfigServer::InitConfigServer(rotable::ConfigServer *config, QWidget *parent) :
    QWidget(parent), configServer(config),
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

    configServer->setValue("Database/host", ui->dbhost->text());
    configServer->setValue("Database/pass", ui->dbpass->text());
    configServer->setValue("Database/user", ui->dbuser->text());
    configServer->setValue("Database/prefix", ui->dbprefix->text());
    configServer->setValue("Network/port", ui->netport->value());
}

void InitConfigServer::on_pushButton_2_clicked()
{
    ui->dbhost->setText("localhost");
    ui->dbprefix->setText("rotable_");
    ui->dbuser->setText("rotable");
    ui->dbpass->setText("rotable");
    ui->netport->setValue(5000);
}
