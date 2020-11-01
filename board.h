#pragma once
#include <string>
#include "cell.h"

class Board
{
    Cell m_state[8][8];
    Board() = default;
public:
    static Board& instance();
    Board(Board&&) = delete;
    Board operator =(Board&&) = delete;
    Board(const Board&) = delete;
    Board operator =(const Board&) = delete;
};
