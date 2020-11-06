#include "chess.h"
#include <iostream>

Chess::Chess() : m_board(Board::instance())
{

}

void Chess::MakeMove(Coordinate From, Coordinate To)
{
    auto cell = m_board.GetCell(From);
    cell.figure->Move(To);
    m_board.UpdateBoard(From, To);
}

void Chess::run()
{
    MakeMove(Coordinate(1, 'a'), Coordinate(1, 'c'));
    m_board.DrawBoard();
}
