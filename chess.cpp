#include "chess.h"
#include <iostream>

Chess::Chess() : m_board(Board::instance())
{

}

void Chess::MakeMove(Coordinate From, Coordinate To)
{
    m_board.Move(From, To);
}

void Chess::run()
{
    MakeMove(Coordinate(1, 'a'), Coordinate(1, 'c'));
}
