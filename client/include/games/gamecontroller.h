#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <games/chess/chess.h>
#include <games/draughts/draughts.h>

class GameController:public QObject
{

    Q_OBJECT

    enum GameName {
      Chess = 2,
      Draughts
    };



public:
        GameController( QObject *parent = 0);

public slots:
    void name(int game);

};

#endif // GAMECONTROLLER_H
