#pragma once
#include <string>
#include "cell.h"
#include "figure.h"
#include <vector>

class Board final
{
    constexpr static const int ROWS = 8;
    constexpr static const int COLUMNS = 8;

    Cell m_state[8][8];
    Board();

    bool CheckDiagonal(Coordinate From, Coordinate To) const;
    bool CheckLine(Coordinate From, Coordinate To) const;
public:
    static Board& instance();
    Board(Board&&) = delete;
    Board operator =(Board&&) = delete;
    Board(const Board&) = delete;
    Board operator =(const Board&) = delete;

    const Cell &GetCell(Coordinate coordinate) const;
    const Cell &GetCell(int x, int y) const;
    void UpdateBoard(Coordinate From, Coordinate To);
    void DrawBoard() const;
    bool VerificationMove(Coordinate From, Coordinate To) const noexcept;
    void Revert(Coordinate From);
    void SetCoordinateForPreview(Coordinate newCoordinate);
    void MakeCellEmpty(Coordinate coordinate);

    ~Board();
};
