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
    Player();
    Player(Color color);
};
