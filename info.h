#pragma once

enum class Type
{
    Pawn,
    King,
    Queen,
    Bishop,
    Knight,
    Rook,
    Empty
};

enum class Color
{
    White,
    Black,
    None
};

struct Info
{
    Color m_color;
    Type m_type;

    Info()
        : m_color{Color::None},
          m_type{Type::Empty}
       {}
    Info(Color color, Type type)
        : m_color{color},
          m_type{type}
    {}
};
