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
};
