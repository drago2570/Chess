#include <iostream>
#include "chess.h"

int main()
{
    Chess chess;
    std::cout << "size " << sizeof (chess) << std::endl;
    chess.run();

    Cell cell;
    auto info = cell.figure->GetInfo();

    std::cout << "type " << (int)info.type << " color " << (int)info.color << " coordinate (" << info.coordinate.x << "; " << info.coordinate.y << ")\n";

    return 0;
}
