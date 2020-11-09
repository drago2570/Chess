#include "player.h"

Player::Player()
    : m_color{Color::None}
{
    m_allAvaliableFigures.reserve(16);
}

Player::Player(Color color)
    : m_color{color}
{
    m_allAvaliableFigures.reserve(16);
}
