#include "figure.h"
#include <iostream>
#include <cmath>

Coordinate IFigure::getCoordinate() const
{
    return m_info.coordinate;
}

Info IFigure::GetInfo() const
{
    return m_info;
}

void Pawn::UpdateCoordinate(Coordinate To)
{
    std::cout << "Pawn Move from (" << m_info.coordinate.x << "; " << m_info.coordinate.y << ") to (" << To.x << "; " << To.y << ")\n";
    m_info.coordinate = To;
}

bool Pawn::CheckMove(Coordinate newCoordinate)
{
    if(m_info.coordinate == newCoordinate) return false;

    constexpr const int BOARD_SIZE = 8;
    int x1 = m_info.coordinate.x;
    int x2 = newCoordinate.x;

    if(m_info.color == Color::White)
    {
        x1 = BOARD_SIZE - m_info.coordinate.x;
        x2 = BOARD_SIZE - newCoordinate.x;
    }

    if(x2 > x1)
    {

        if(!isFirstMove && ( abs(m_info.coordinate.x - newCoordinate.x) == 2 && m_info.coordinate.y == newCoordinate.y))
        {
            isFirstMove = true;
            isFirstLongMove = true;
            return true;
        }

        if( ( abs(m_info.coordinate.x - newCoordinate.x) == 1 && m_info.coordinate.y == newCoordinate.y)
                || ( abs(m_info.coordinate.y - newCoordinate.y) == 1 && abs(m_info.coordinate.x - newCoordinate.x) == 1 ) )
        {
            isFirstMove = true;
            return true;
        }
    }
    return false;
}

void King::UpdateCoordinate(Coordinate To)
{
    m_info.coordinate = To;
}

bool King::CheckMove(Coordinate newCoordinate)
{
    if( m_info.coordinate != newCoordinate
        && ( ( (abs(m_info.coordinate.y - newCoordinate.y) == 1) && (m_info.coordinate.x - newCoordinate.x) == 0 ) // left right
        || ( (abs(m_info.coordinate.x - newCoordinate.x) == 1) && (m_info.coordinate.y - newCoordinate.y) == 0) // ahead down
        || ( (abs(m_info.coordinate.y - newCoordinate.y) == 1) && abs(m_info.coordinate.x - newCoordinate.x) == 1) ) ) // diagonal
    {
        return true;
    }
    return false;
}

void Queen::UpdateCoordinate(Coordinate To)
{
    m_info.coordinate = To;
}

bool Queen::CheckMove(Coordinate newCoordinate)
{
    if(m_info.coordinate != newCoordinate
        && ( abs(m_info.coordinate.y - newCoordinate.y) == abs(m_info.coordinate.x - newCoordinate.x) )
        && ( pow(m_info.coordinate.y - newCoordinate.y, 2) + pow(m_info.coordinate.x - newCoordinate.x, 2) == 5) )
            return true;

    return false;
}

void Bishop::UpdateCoordinate(Coordinate To)
{
    m_info.coordinate = To;
}

bool Bishop::CheckMove(Coordinate newCoordinate)
{
    if( m_info.coordinate != newCoordinate
            && ( abs(m_info.coordinate.y - newCoordinate.y) == abs(m_info.coordinate.x - newCoordinate.x)) )
    {
        return true;
    }

    return false;
}

void Knight::UpdateCoordinate(Coordinate To)
{
    m_info.coordinate = To;
}

bool Knight::CheckMove(Coordinate newCoordinate)
{
    if(m_info.coordinate != newCoordinate
            && ( pow(m_info.coordinate.y - newCoordinate.y, 2) + pow(m_info.coordinate.x - newCoordinate.x, 2) == 5) )
    {
        return true;
    }

    return false;
}

void Rook::UpdateCoordinate(Coordinate To)
{
    m_info.coordinate = To;
}

bool Rook::CheckMove(Coordinate newCoordinate)
{
    if( m_info.coordinate != newCoordinate &&
            ( m_info.coordinate.y == newCoordinate.y || m_info.coordinate.x == newCoordinate.x) )
    {
        return true;
    }

    return false;
}

void Empty::UpdateCoordinate(Coordinate To)
{
    std::cout << "Empty Move from (" << m_info.coordinate.x << "; " << m_info.coordinate.y << ") to (" << To.x << "; " << To.y << ")\n";
    m_info.coordinate = To;
}
