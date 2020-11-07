#include "chess.h"
#include <iostream>

Chess::Chess() : m_board(Board::instance())
{}

void Chess::MakeMove(Coordinate From, Coordinate To)
{
    auto cell = m_board.GetCell(From);
    if(cell.figure->CheckMove(To) && m_board.VerificationMove(From, To))
    {
        cell.figure->UpdateCoordinate(To);
        m_board.UpdateBoard(From, To);
    }

    m_board.DrawBoard();
}

void Chess::run()
{
    MakeMove(Coordinate(1, 'a'), Coordinate(2, 'a'));
}
