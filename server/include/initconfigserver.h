#ifndef INITCONFIGSERVER_H
#define INITCONFIGSERVER_H

#include <QWidget>

namespace Ui {
class InitConfigServer;
}

class InitConfigServer : public QWidget
{
    Q_OBJECT

public:
    explicit InitConfigServer(QWidget *parent = 0);
    ~InitConfigServer();

private:
    Ui::InitConfigServer *ui;
};

#endif // INITCONFIGSERVER_H
