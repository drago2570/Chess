#include "figure.h"
#include <iostream>
#include <cmath>
#include <map>
#include <algorithm>
Coordinate IFigure::getCoordinate() const
{
    return m_info.coordinate;
}

const Info& IFigure::GetInfo() const
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

std::vector<Coordinate> Pawn::GeneratePossibleMoves()
{
    std::vector<Coordinate> possibleMove;
    Coordinate moves[3];
    if(m_info.color == Color::Black)
    {
        moves[0] = m_info.coordinate - 1;
        moves[1] = m_info.coordinate + std::make_pair(1, static_cast<char>(1));
        moves[2] = m_info.coordinate + std::make_pair(1, -static_cast<char>(1));
    }
    else
    {
        moves[0] = m_info.coordinate + 1;
        moves[1] = m_info.coordinate - std::make_pair(1, static_cast<char>(1));
        moves[2] = m_info.coordinate - std::make_pair(1, -static_cast<char>(1));
    }

    for(auto& move : moves)
    {
        if(Coordinate::ValidateCoordinate(move))
        {
            possibleMove.push_back(move);
        }
    }

    return possibleMove;
}

bool King::isFirstMove() const
{
    return m_isFirstMove;
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
        m_isFirstMove = true;
        return true;
    }
    return false;
}

std::vector<Coordinate> King::GeneratePossibleMoves()
{
    std::vector<Coordinate> possibleMove;

    Coordinate moves[6] = {
        m_info.coordinate - 1,
        m_info.coordinate + 1,
        m_info.coordinate - static_cast<char>(1),
        m_info.coordinate + static_cast<char>(1),
        m_info.coordinate - std::make_pair(1, static_cast<char>(1)),
        m_info.coordinate + std::make_pair(1, static_cast<char>(1))
    };

    for(auto& move : moves)
    {
        if(Coordinate::ValidateCoordinate(move))
        {
            possibleMove.push_back(move);
        }
    }

    return possibleMove;
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

std::vector<Coordinate> Queen::GeneratePossibleMoves()
{
    return {};
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

std::vector<Coordinate> Bishop::GeneratePossibleMoves()
{
    std::vector<Coordinate> possibleMove;
    std::vector<Coordinate> starts;

    for(int i = 0; i < 8; ++i)
        if(CheckMove(Coordinate(0, i)))
            starts.emplace_back(0, i); // first left, second right

    auto maxIteration = [](Coordinate first, Coordinate second) -> int
    { return first.y > second.y ? first.y + 1 : second.y + 1; };

    for(int i = 0; maxIteration(starts[0], starts[1]); --i)
    {
        auto[x1, y1] = Coordinate::GetXY(starts[0]);
        auto[x2, y2] = Coordinate::GetXY(starts[1]);

        if((Coordinate(x1-i, y1-i) != m_info.coordinate)
                && Coordinate::ValidateCoordinate(x1-i, y1-i))
        {
            possibleMove.emplace_back((x1-i), (y1-i));
        }
        if((Coordinate(x2-i, y2-i) == m_info.coordinate)
           && Coordinate::ValidateCoordinate(x2-i, y2-i))
        {
            possibleMove.emplace_back((x2-i), (y2-i));
        }
    }

    return possibleMove;
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

std::vector<Coordinate> Knight::GeneratePossibleMoves()
{
    std::vector<Coordinate> possibleMove;

    /*
        *******
        **1*2**
        *3***5*
        ***@***
        *4***6*
        **7*8**
        *******
    */

    Coordinate moves[8] = {
        m_info.coordinate + std::make_pair(2, static_cast<char>(1)), // 1
        m_info.coordinate + std::make_pair(2, -static_cast<char>(1)), // 2

        m_info.coordinate - std::make_pair(1, static_cast<char>(2)), // 3
        m_info.coordinate - std::make_pair(-1, static_cast<char>(2)), // 4

        m_info.coordinate + std::make_pair(1, static_cast<char>(2)), // 5
        m_info.coordinate + std::make_pair(-1, static_cast<char>(2)), // 6

        m_info.coordinate + std::make_pair(2, -static_cast<char>(1)), // 7
        m_info.coordinate + std::make_pair(2, static_cast<char>(1)), // 8
    };

    for(auto& move : moves)
    {
        if(Coordinate::ValidateCoordinate(move))
        {
            possibleMove.push_back(move);
        }
    }

    return possibleMove;
}

bool Rook::isFirstMove() const
{
    return m_isFirstMove;
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
        m_isFirstMove = true;
        return true;
    }

    return false;
}

std::vector<Coordinate> Rook::GeneratePossibleMoves()
{
    std::vector<Coordinate> possibleMove;

    for(int i = 0; i < 8; ++i)
    {
        if(m_info.coordinate != Coordinate(i, m_info.coordinate.y)) // vert
        {
            possibleMove.push_back(Coordinate(i, m_info.coordinate.y));
        }

        if(m_info.coordinate != Coordinate(m_info.coordinate.x, i)) // horis
        {
            possibleMove.push_back(Coordinate(m_info.coordinate.x, i));
        }
    }

    return possibleMove;
}

void Empty::UpdateCoordinate(Coordinate To)
{
    std::cout << "Empty Move from (" << m_info.coordinate.x << "; " << m_info.coordinate.y << ") to (" << To.x << "; " << To.y << ")\n";
    m_info.coordinate = To;
}
