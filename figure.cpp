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

    /*
        * * * 0 * * * *
        0 * 0 * * * * *
        * 1 * * * * * *
        0 * 0 * * * * *
        * * * 0 * * * *
        * * * * 0 * * *
        * * * * * 0 * *
        * * * * * * 0 *

        1(2, 1)

        0 * * * * * * *
        * 0 * * * * * *
        * * 0 * * * * *
        * * * 0 * * * 0
        * * * * 0 * 0 *
        * * * * * 1 * *
        * * * * 0 * 0 *
        * * * 0 * * * 0

        1(5, 5)

        * * * 1 * * * *
        * * 0 * 0 * * *
        * 0 * * * 0 * *
        0 * * * * * 0 *
        * * * * * * * 0
        * * * * * * * *
        * * * * * * * *
        * * * * * * * *

        1(0, 3)

    */

    Coordinate A(0,0);
    Coordinate B(7,7);
    Coordinate C = m_info.coordinate;
    auto [x1, y1] = Coordinate::GetXY(A);
    auto [x2, y2] = Coordinate::GetXY(B);
    auto [x3, y3] = Coordinate::GetXY(C);
    int D = (x3-x1) * (y2-y1) - (y3-y1) * (x2-x1);

    std::cout << D << std::endl;

    Coordinate K(0,7);
    Coordinate L(7,0);
    Coordinate M = m_info.coordinate;
    auto [x11, y11] = Coordinate::GetXY(K);
    auto [x12, y12] = Coordinate::GetXY(L);
    auto [x13, y13] = Coordinate::GetXY(M);
    int N = (x13-x11) * (y12-y11) - (y13-y11) * (x12-x11);

    std::cout << N << std::endl;

//    auto currentCoordinate = m_info.coordinate;

//    // left up corner
//    auto startPosition = currentCoordinate-std::make_pair<int, char>(1,static_cast<char>(1));
//    for(int i = 1; Coordinate::ValidateCoordinate(startPosition); ++i)
//    {
//        startPosition.ChangeXY(-i,-i);
//    }

//    // right down corner
//    startPosition = currentCoordinate+std::make_pair<int, char>( 1,static_cast<char>(1) );
//    for(int i = 1; Coordinate::ValidateCoordinate(startPosition); ++i)
//    {
//        startPosition.ChangeXY(i,i);
//    }

//    // right up corner
//    startPosition = currentCoordinate+std::make_pair<int, char>(-1, static_cast<char>(1) );
//    for(int i = 1; Coordinate::ValidateCoordinate(startPosition); ++i)
//    {
//        startPosition.ChangeXY(-i,i);
//    }

//    // left down corner
//    startPosition = currentCoordinate+std::make_pair<int, char>( 1, -static_cast<char>(1) );
//    for(int i = 1; Coordinate::ValidateCoordinate(startPosition); ++i)
//    {
//        startPosition.ChangeXY(i,-i);
//    }

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
