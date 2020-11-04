#pragma once
#include <map>

struct Coordinate final
{
    short int x;
    char y;

    Coordinate(short int x, char y)
        :x{x}, y{y}
       {}

    Coordinate()
        : x{-1}, y{'z'}
    {}

    static std::pair<int, int>GetXY(Coordinate coordinate)
    {
        return {coordinate.x, coordinate.y - 'a'};
    }
};
