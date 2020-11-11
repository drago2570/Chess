#pragma once
#include "coordinate.h"
#include <iostream>
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
    Coordinate coordinate;
    Color color;
    Type type;

    Info()
        : color{Color::None},
          type{Type::Empty}
    {
//        std::cout << "Info() " << (int)color << " " << (int)type << std::endl;
    }
    Info(int x, char y, Color color, Type type)
        : coordinate{Coordinate(x,y)},
          color{color},
          type{type}

    {
//        std::cout << "Info(params) " << (int)color << " " << (int)type << std::endl;
    }
};
