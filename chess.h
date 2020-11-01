#pragma once
#include "board.h"
#include "player.h"

class Chess
{
    Board& m_board;
    Player m_players[2];
public:
    Chess();
};
