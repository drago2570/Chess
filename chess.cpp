#include "chess.h"
#include <iostream>

Chess::Chess()
    : m_board(Board::instance()),
      m_players{Player{Color::White}, Player{Color::Black}}
{}

void Chess::MakeMove(Coordinate From, Coordinate To)
{
    const Cell& cellFrom = m_board.GetCell(From);
    const Cell& cellTo = m_board.GetCell(To);
//    auto infoFrom = cellFrom.figure->GetInfo();
//    auto infoTo = cellTo.figure->GetInfo();

    if(cellFrom.figure->CheckMove(To)
            && m_board.VerificationMove(From, To)
            && cellTo.figure->GetInfo().type == Type::Empty)
    {
        cellFrom.figure->UpdateCoordinate(To);
        m_board.UpdateBoard(From, To);
    }
    else
    {
        m_board.Revert(From);
        std::cout << "invalid move\n";
    }

    m_board.DrawBoard();
}

void Chess::run()
{
    try {
        m_board.DrawBoard();
    } catch (...) {
        std::cout << "Error\n";
    }

    MakeMove(Coordinate(1, 'a'), Coordinate(2, 'a'));
    MakeMove(Coordinate(2, 'a'), Coordinate(1, 'a'));
}
