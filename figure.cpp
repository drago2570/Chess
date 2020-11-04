#include "figure.h"
#include <iostream>

Coordinate IFigure::getCoordinate() const
{
    return m_info.coordinate;
}

Info IFigure::GetInfo() const
{
    return m_info;
}

void Pawn::Move(Coordinate To)
{
    std::cout << "Pawn Move from (" << m_info.coordinate.x << "; " << m_info.coordinate.y << ") to (" << To.x << "; " << To.y << ")\n";
    m_info.coordinate = To;
}

void King::Move(Coordinate To)
{
    m_info.coordinate = To;
}

void Queen::Move(Coordinate To)
{
    m_info.coordinate = To;
}

void Bishop::Move(Coordinate To)
{
    m_info.coordinate = To;
}

void Knight::Move(Coordinate To)
{
    m_info.coordinate = To;
}

void Rook::Move(Coordinate To)
{
    m_info.coordinate = To;
}

void Empty::Move(Coordinate To)
{
    std::cout << "Empty Move from (" << m_info.coordinate.x << "; " << m_info.coordinate.y << ") to (" << To.x << "; " << To.y << ")\n";
    m_info.coordinate = To;
}
