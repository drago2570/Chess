#pragma once
#include <map>
#include <istream>

struct Coordinate final
{
    int x;
    char y;

    Coordinate(int x, char y)
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

    static bool ValidateCoordinate(Coordinate coordinate)
    {
        return (coordinate.x >= 0 && coordinate.x <= 7) && ((coordinate.y >= 'a' && coordinate.y <= 'h'));
    }

    friend bool operator==(Coordinate first, Coordinate second)
    { return first.x == second.x && first.y == second.y; }

    friend bool operator!=(Coordinate first, Coordinate second)
    { return !(first == second); }

    friend bool operator>(Coordinate first, Coordinate second)
    { return first.x > second.x;}

    friend bool operator<(Coordinate first, Coordinate second)
    { return first.x < second.x;}

    friend std::istream& operator >> (std::istream &is, Coordinate &coordinate)
    {
        is >> coordinate.x >> coordinate.y;
        coordinate.y = std::tolower(coordinate.y);
        return is;
    }
};
