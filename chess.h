#pragma once
#include "board.h"
#include "player.h"

class Chess final
{
    Board& m_board;
    Player m_players[2];

    void Castilng(Coordinate From, Coordinate To);
    void MakeMove(Coordinate From, Coordinate To);
    bool IsCheck(Coordinate coordinate); // шах
    bool IsCheckmate(); // мат
    bool IsCastlingPosible(Coordinate From, Coordinate To); // рокировка
    bool IsStalemate(); // пат
public:
    Chess();
    void run();
    ~Chess(){std::cout << "~Chess()\n";}
};
