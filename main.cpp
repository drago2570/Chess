#include <iostream>
#include "chess.h"

int main()
{
    Chess chess;
    std::cout << "size " << sizeof (chess) << std::endl;
    chess.run();
    return 0;
}
