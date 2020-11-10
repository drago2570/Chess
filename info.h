#pragma once
#include "coordinate.h"

enum class Type
{
    Pawn=0,
    King=1,
    Queen=2,
    Bishop=3,
    Knight=4,
    Rook=5,
    Empty=6
};

enum class Color
{
    White=0,
    Black=1,
    None=2
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
