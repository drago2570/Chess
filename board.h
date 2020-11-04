#pragma once
#include <string>
#include "cell.h"
#include "figure.h"

class Board final
{
    Cell m_state[8][8] = {
        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
        {Cell(new Pawn(1, 'a', Color::Black)),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},

        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},

        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
    };
    Board() = default;
public:
    static Board& instance();
    Board(Board&&) = delete;
    Board operator =(Board&&) = delete;
    Board(const Board&) = delete;
    Board operator =(const Board&) = delete;
    void Move(Coordinate From, Coordinate To);
};
