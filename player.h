#pragma once
#include <vector>
#include "coordinate.h"
#include "cell.h"

class Player final
{
    std::vector<Coordinate> m_avaliableFigureToReturn;
    std::vector<Cell> m_allAvaliableFigures;
    Color m_color;
    Coordinate m_kingCoordinate;
public:
    Player(): m_color{Color::None}
    {
        m_allAvaliableFigures.reserve(16);
    }
    Player(Color color)
        : m_color{color}
    {
        m_allAvaliableFigures.reserve(16);
    }
};
