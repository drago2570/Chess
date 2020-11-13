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

    static bool ValidateCoordinate(Coordinate coordinate) noexcept
    {
        return (coordinate.x >= 0 && coordinate.x <= 7) && ((coordinate.y >= 'a' && coordinate.y <= 'h'));
    }

    static bool ValidateCoordinate(int x, int y) noexcept
    {
        return (x >= 0 && x <= 7) && ((static_cast<char>(y) >= 'a' && static_cast<char>(y) <= 'h'));
    }

    friend bool operator==(Coordinate first, Coordinate second)
    { return first.x == second.x && first.y == second.y; }

    friend bool operator!=(Coordinate first, Coordinate second)
    { return !(first == second); }

    friend bool operator>(Coordinate first, Coordinate second)
    { return first.x > second.x;}

//    friend bool operator<(Coordinate first, Coordinate second)
//    { return first.x < second.x;}

    friend bool operator<(Coordinate first, Coordinate second)
    { return first.y < second.y;}

    friend std::istream& operator >> (std::istream &is, Coordinate &coordinate)
    {
        is >> coordinate.x >> coordinate.y;
        coordinate.y = std::tolower(coordinate.y);
        return is;
    }

    Coordinate operator-(std::pair<int, char> coordinate)
    {
        auto [_x, _y] = coordinate;
        return Coordinate(x-_x, y-_y);
    }

    Coordinate operator-(int x)
    {
        return Coordinate(x-x, y);
    }

    Coordinate operator-(char y)
    {
        return Coordinate(x, y-y);
    }

    Coordinate operator+(std::pair<int, char> coordinate)
    {
        auto [_x, _y] = coordinate;
        return Coordinate(x+_x, y+_y);
    }

    Coordinate operator+(int x)
    {
        return Coordinate(x+x, y);
    }


    Coordinate operator+(char y)
    {
        return Coordinate(x, y+y);
    }
};
