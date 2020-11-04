#include "board.h"

Board &Board::instance()
{
    static Board inst;
    return inst;
}

void Board::Move(Coordinate From, Coordinate To)
{
    auto [x, y] = Coordinate::GetXY(From);
    m_state[x][y].figure->Move(To);
}
