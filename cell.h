#pragma once
#include "figure.h"

struct Cell final
{
    IFigure* figure;
    const Info* previewInfo = nullptr; // init figure->GetInfo() ?
    // Take previewInfo to investigate move is really possible, after update figure->info
    // after init previewInfo(figure->GetInfo() or nullptr)
    Cell()
        :figure{new Empty()}
    {}
    Cell(IFigure* figure)
        : figure{figure},
          previewInfo{&figure->GetInfo()}
    {}

    ~Cell()
    {
        delete figure;
    }
};
