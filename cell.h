#pragma once
#include "figure.h"
#include <memory>

struct Cell final
{
    std::unique_ptr<IFigure> figure;
    Info previewInfo = figure->GetInfo();
    // Take previewInfo to investigate move is really possible, after update figure->info
    // after init previewInfo(figure->GetInfo())
    Cell()
        :figure{new Empty()}
    {}

    Cell(std::unique_ptr<IFigure> figure)
        :figure{std::move(figure)}
    {}

    Cell(const Cell&) = delete;
    Cell& operator=(const Cell&) = delete;
    Cell(Cell&&) = delete;
    Cell& operator=(Cell&& other)
    {
        figure = std::move(other.figure);
        previewInfo = figure->GetInfo();
        return *this;
    }

    void SetPreviewInfoByFigure()
    {
        previewInfo = figure->GetInfo();
    }

    ~Cell()
    {}
};
