#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

class gamecontroller
{

    Q_OBJECT

    Q_PROPERTY(QString pieces READ pieces NOTIFY piecesChanged)

    public:
        explicit GameController(QObject* t_parent = nullptr);
};

#endif // GAMECONTROLLER_H
