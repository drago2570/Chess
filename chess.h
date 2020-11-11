#pragma once
#include "board.h"
#include "player.h"

class Chess final
{
    Board& m_board;
    Player m_players[2];
    Color m_currentPlayer;

    void Castilng(Coordinate From, Coordinate To);
    void MakeMove(Coordinate From, Coordinate To);
    bool IsMoveSafe() const;
    std::pair<Coordinate, Coordinate> ReadFromUser();
    bool IsCheck(Coordinate coordinate); // шах
    bool IsCheckmate(Coordinate coordinate, Coordinate kingCoordinate, std::vector<Coordinate> threatFigures); // мат
    bool IsCastlingPosible(Coordinate From, Coordinate To); // рокировка
    bool IsStalemate(); // пат
public:
    Chess();
    void run();
    ~Chess(){std::cout << "~Chess()\n";}
};
