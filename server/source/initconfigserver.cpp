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
