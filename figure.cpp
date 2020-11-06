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
    if(CheckMove(To))
    {}
    std::cout << "Pawn Move from (" << m_info.coordinate.x << "; " << m_info.coordinate.y << ") to (" << To.x << "; " << To.y << ")\n";
    m_info.coordinate = To;
}

void King::Move(Coordinate To)
{
    if(CheckMove(To))
    {}
    m_info.coordinate = To;
}

void Queen::Move(Coordinate To)
{
    if(CheckMove(To))
    {}
    m_info.coordinate = To;
}

void Bishop::Move(Coordinate To)
{
    if(CheckMove(To))
    {}
    m_info.coordinate = To;
}

void Knight::Move(Coordinate To)
{
    if(CheckMove(To))
    {}
    m_info.coordinate = To;
}

void Rook::Move(Coordinate To)
{
    if(CheckMove(To))
    {}
    m_info.coordinate = To;
}

void Empty::Move(Coordinate To)
{
    if(CheckMove(To))
    {}
    std::cout << "Empty Move from (" << m_info.coordinate.x << "; " << m_info.coordinate.y << ") to (" << To.x << "; " << To.y << ")\n";
    m_info.coordinate = To;
}
