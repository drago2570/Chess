#pragma once
#include "board.h"
#include "player.h"

class Chess final
{
    Board& m_board;
    Player m_players[2];
public:
    Chess();
    void MakeMove(Coordinate From, Coordinate To);
    void run();
};
