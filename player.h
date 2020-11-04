#pragma once
#include <vector>
#include "coordinate.h"
#include "cell.h"

class Player final
{
    std::vector<Coordinate> m_avaliableFigureToReturn;
    std::vector<Cell> m_allAvaliableFigures;
    const char* m_color;
public:
    Player();
    Player(const char* color)
        : m_color{color}
    {}
};
