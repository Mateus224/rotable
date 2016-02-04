#ifndef INITCONFIGSERVER_H
#define INITCONFIGSERVER_H

#include <QWidget>
#include "configserver.h"

namespace Ui {
class InitConfigServer;
}

class InitConfigServer : public QWidget
{
    Q_OBJECT

public:
    explicit InitConfigServer(rotable::ConfigServer* config, QWidget *parent = 0);
    ~InitConfigServer();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::InitConfigServer *ui;
    rotable::ConfigServer *configServer;
};

#endif // INITCONFIGSERVER_H
