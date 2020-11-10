#pragma once
#include <string>
#include "cell.h"
#include "figure.h"

class Board final
{
    constexpr static const int ROWS = 8;
    constexpr static const int COLUMNS = 8;

    Cell m_state[8][8]
    = {
        {Cell(new Rook(0, 'a', Color::Black)),Cell(new Knight(0, 'b', Color::Black)),Cell(new Bishop(0, 'c', Color::Black)),
         Cell(new Queen(0, 'd', Color::Black)),Cell(new King(0, 'e', Color::Black)),Cell(new Bishop(0, 'f', Color::Black)),
         Cell(new Knight(0, 'g', Color::Black)),Cell(new Rook(0, 'h', Color::Black))},

        {Cell(new Pawn(1, 'a', Color::Black)),Cell(new Pawn(1, 'b', Color::Black)),Cell(new Pawn(1, 'c', Color::Black)),
         Cell(new Pawn(1, 'd', Color::Black)),Cell(new Pawn(1, 'e', Color::Black)),Cell(new Pawn(1, 'f', Color::Black)),
         Cell(new Pawn(1, 'g', Color::Black)),Cell(new Pawn(1, 'h', Color::Black))},

        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},
        {Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell(),Cell()},

        {Cell(new Pawn(6, 'a', Color::White)),Cell(new Pawn(6, 'b', Color::White)),Cell(new Pawn(6, 'c', Color::White)),
         Cell(new Pawn(6, 'd', Color::White)),Cell(new Pawn(6, 'e', Color::White)),Cell(new Pawn(6, 'f', Color::White)),
         Cell(new Pawn(6, 'g', Color::White)),Cell(new Pawn(6, 'h', Color::White))},

        {Cell(new Rook(7, 'a', Color::White)),Cell(new Knight(7, 'b', Color::White)),Cell(new Bishop(7, 'c', Color::White)),
         Cell(new Queen(7, 'd', Color::White)),Cell(new King(7, 'e', Color::White)),Cell(new Bishop(7, 'f', Color::White)),
         Cell(new Knight(7, 'g', Color::White)),Cell(new Rook(7, 'h', Color::White))},
    };
    Board(); // = default;

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
    void DrawBoard() const noexcept;
    bool VerificationMove(Coordinate From, Coordinate To) const noexcept;
};
