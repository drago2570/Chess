#pragma once
#include "figure.h"
#include <memory>

struct Cell final
{
    std::unique_ptr<IFigure> figure;
    Info previewInfo = figure->GetInfo();
    // Take previewInfo to investigate move is really possible, after update figure->info
    // after init previewInfo(figure->GetInfo() or nullptr)
    Cell()
        :figure{new Empty()}
    {
        std::cout << "Cell()\n";
    }
    Cell(std::unique_ptr<IFigure> figure)
        :figure{std::move(figure)}
    {}

    Cell(const Cell&) = delete;
    Cell& operator=(const Cell&) = delete;
    Cell(Cell&&) = delete;
    Cell& operator=(Cell&& other)
    {
        std::cout << "Cell& operator=(Cell&& other)\n";
        figure = std::move(other.figure);
        previewInfo = figure->GetInfo();
        std::cout << "Cell& operator=(Cell&& other) type " << (int)figure->GetInfo().type << std::endl;
        return *this;
    }

    void SetPreviewInfoByFigure()
    {
        previewInfo = figure->GetInfo();
    }

    ~Cell()
    {
        std::cout << "~Cell() color ";
    }
};
