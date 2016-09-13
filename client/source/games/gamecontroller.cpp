#include "games/gamecontroller.h"

GameController::GameController( QObject *parent)
    : QObject(parent)
{
   // m_board.setFen(m_board.START_FEN);
}

void GameController::name(int game) {
    switch (game) {
    case Chess:
        new chess;
        break;

    case Draughts:
        new draughts;
        break;

    default:
        break;
    }


}
