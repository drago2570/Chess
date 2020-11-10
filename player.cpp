#include "player.h"
#include <iostream>

const std::vector<Coordinate>& Player::allAvaliableFigures() const
{
    return m_allAvaliableFigures;
}

void Player::DeleteFigure(Type type, Coordinate coordinate)
{
    AddFigureForReturn(type);
}

void Player::ReturnFigureToBoard(Type type)
{
    // Enter coordinate
    AddFigure(Coordinate());
}

void Player::AddFigureForReturn(Type type)
{

}

void Player::AddFigure(Coordinate coordinate)
{

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
}
