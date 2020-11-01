#pragma once

struct Coordinate
{
    short int x;
    char y;

    Coordinate(short int x, char y)
        :x{x}, y{y}
       {}

    Coordinate() = default;
};
