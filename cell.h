#pragma once
#include "figure.h"

struct Cell final
{
    IFigure* figure;

    Cell()
        :figure{new Empty()}
    {}
    Cell(IFigure* figure)
        : figure{figure}
    {}

    ~Cell()
    {
        delete figure;
    }
};
