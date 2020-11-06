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
    m_board.DrawBoard();
}

void Chess::run()
{
    MakeMove(Coordinate(1, 'a'), Coordinate(2, 'a'));
}
