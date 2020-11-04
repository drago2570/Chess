#pragma once
#include "coordinate.h"

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

struct Info final
{
    Color color;
    Type type;
    Coordinate coordinate;

    Info()
        : color{Color::None},
          type{Type::Empty}
       {}
    Info(int x, char y, Color color, Type type)
        : color{color},
          type{type},
          coordinate{Coordinate(x,y)}
    {}
};
