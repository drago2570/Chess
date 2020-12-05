#include "player.h"
#include <iostream>
#include <algorithm>

const std::vector<Coordinate>& Player::allAvaliableFigures() const
{
    return m_allAvaliableFigures;
}

void Player::DeleteFigure(Type type, Coordinate coordinate)
{
    auto res = std::find(begin(m_allAvaliableFigures), end(m_allAvaliableFigures), coordinate);

    if(res == end(m_allAvaliableFigures)) return;

    AddFigureForReturn(type);
}

Info Player::ReturnFigureToBoard()
{
    // Enter coordinate
    Coordinate coordinate;
    // print m_avaliableFigureToReturn
    // read type
    Type type = Type::Empty;
    std::cout << "Enter coordinate: ";
    std::cin >> coordinate;

    AddFigure(coordinate);

    return Info{coordinate, m_color, type};
}

const Coordinate Player::kingCoordinate() const
{
    return m_kingCoordinate;
}

std::size_t Player::UpdateCoordinateForPlayer(Coordinate From, Coordinate To)
{
    auto it = find(begin(m_allAvaliableFigures), end(m_allAvaliableFigures), From);
//    auto currentCoordinate = *it;
    *it = std::move(To);
    if(From == m_kingCoordinate)
    {
        m_kingCoordinate = *it;
    }
    return std::distance(begin(m_allAvaliableFigures), it);
}

void Player::UpdateCoordinateForPlayer(size_t position, Coordinate coordinate)
{
    if(coordinate == m_kingCoordinate)
    {
        m_kingCoordinate = coordinate;
    }

    m_allAvaliableFigures[position] = coordinate;
}

void Player::AddFigureForReturn(Type type)
{
    m_avaliableFigureToReturn.push_back(type);
}

void Player::AddFigure(Coordinate coordinate)
{
    m_allAvaliableFigures.push_back(coordinate);
}

Player::Player()
    : m_color{Color::None}
{}

Player::Player(Color color)
    : m_color{color}
{
    m_allAvaliableFigures.reserve(16);

    char c = 'a';
    for(int i = 0; i < 16; ++i, ++c)
    {
        if(i == 8)
        {
            c = 'a';
        }
        m_allAvaliableFigures.push_back(Coordinate( m_color == Color::Black ? (i/8) : (7 - (i/8)), c));
    }

    m_kingCoordinate = m_color == Color::Black ? Coordinate(0, 'e') : Coordinate(7, 'e');
}
