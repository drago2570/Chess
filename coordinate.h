#pragma once
#include <map>

struct Coordinate final
{
    int x;
    char y;

    Coordinate(short int x, char y)
        :x{x}, y{y}
       {}

    Coordinate()
        : x{-1}, y{'z'}
    {}

    static std::pair<int, int>GetXY(Coordinate coordinate) noexcept
    {
        return {coordinate.x, coordinate.y - 'a'};
    }

    static int GetX(Coordinate coordinate) noexcept
    {
        return coordinate.x;
    }

    static int GetY(Coordinate coordinate) noexcept
    {
        return coordinate.y - 'a';
    }
    friend bool operator==(Coordinate first, Coordinate second)
    { return first.x == second.x && first.y == second.y; }

    friend bool operator!=(Coordinate first, Coordinate second)
    { return !(first == second); }

    friend bool operator>(Coordinate first, Coordinate second)
    { return first.x > second.x;}

    friend bool operator<(Coordinate first, Coordinate second)
    { return first.x < second.x;}
};
