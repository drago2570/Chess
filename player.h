#pragma once
#include <vector>
#include "coordinate.h"
#include "cell.h"

class Player final
{
    std::vector<Type> m_avaliableFigureToReturn;
    std::vector<Coordinate> m_allAvaliableFigures;
    Color m_color;
    Coordinate m_kingCoordinate;

    void AddFigureForReturn(Type type);
    void AddFigure(Coordinate coordinate);
public:
    Player();
    Player(Color color);

    const std::vector<Coordinate>& allAvaliableFigures() const;
    void DeleteFigure(Type type, Coordinate coordinate);
    Info ReturnFigureToBoard();
    const Coordinate kingCoordinate() const;
    std::size_t UpdateCoordinateForPlayer(Coordinate From, Coordinate To);
    void UpdateCoordinateForPlayer(size_t position, Coordinate coordinate);
};
