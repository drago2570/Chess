#include "board.h"

Board &Board::instance()
{
    static Board inst;
    return inst;
}
