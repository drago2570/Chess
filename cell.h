#pragma once
#include "figure.h"

struct Cell
{
    IFigure* m_figure;

    Cell() = default;
    Cell(IFigure* figure)
        : m_figure{figure}
    {}
};
