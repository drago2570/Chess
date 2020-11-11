#include "chess.h"
#include <iostream>

Chess::Chess()
    : m_board(Board::instance()),
      m_players{Player{Color::White}, Player{Color::Black}},
      m_currentPlayer{Color::Black}
{}

Color operator!(Color color)
{
    return color == Color::Black ? Color::White : Color::Black;
}

void Chess::MakeMove(Coordinate From, Coordinate To)
{
    const Cell& cellFrom = m_board.GetCell(From);
    const Cell& cellTo = m_board.GetCell(To);

    if(cellFrom.figure->CheckMove(To)
            && m_board.VerificationMove(From, To)
            && cellTo.figure->GetInfo().type == Type::Empty)
    {
        cellFrom.figure->UpdateCoordinate(To);
//        m_board.SetCoordinateForPreview(From); need to do

        if(IsMoveSafe())
        {
            m_board.UpdateBoard(From, To);
        }
        else
        {
            m_board.Revert(From);
        }

//        if(!IsCheck(To)
//        {
//            m_board.UpdateBoard(From, To);
//        }
//        else
//        {
//            m_board.Revert(From);
//        }
        m_currentPlayer = !m_currentPlayer;
    }
    else
    {
        std::cout << "invalid move\n";
    }

    m_board.DrawBoard();
}

bool Chess::IsMoveSafe() const
{
    auto kingCoordinate = m_players[static_cast<int>(m_currentPlayer)].kingCoordinate();
    decltype(auto) threatFigures = m_players[static_cast<int>(!m_currentPlayer)].allAvaliableFigures();

    for(auto& coordinate : threatFigures)
    {
        decltype(auto) figure = m_board.GetCell(coordinate);
        if(figure.figure->CheckMove(kingCoordinate))
        {
            return false;
        }
    }

    return true;
}

std::pair<Coordinate, Coordinate> Chess::ReadFromUser()
{
    std::cout << "Enter coordinates: ";
    Coordinate From;
    std::cin >> From;
    Coordinate To;
    std::cin >> To;
    return {From, To};
}

bool Chess::IsCheck(Coordinate coordinate)
{
    auto kingCoordinate = m_players[static_cast<int>(!m_currentPlayer)].kingCoordinate();
    if(m_board.GetCell(coordinate).figure->CheckMove(kingCoordinate))
    {
        return true;
    }

    return false;
}

bool Chess::IsCastlingPosible(Coordinate From, Coordinate To)
{
    decltype(auto) cellFrom = m_board.GetCell(From);
    decltype(auto) cellTo = m_board.GetCell(To);

    if( (cellFrom.figure->GetInfo().type == Type::King && dynamic_cast<King*>(cellFrom.figure.get())->isFirstMove())
            && (cellTo.figure->GetInfo().type == Type::Rook && dynamic_cast<Rook*>(cellTo.figure.get())->isFirstMove()) )
    {
        return true;
    }
    // TODO: Check line from king to Rook
    return false;
}

void Chess::run()
{
    m_board.DrawBoard();

    auto[From, To] = ReadFromUser();

    if( !Coordinate::ValidateCoordinate(From)
            || !Coordinate::ValidateCoordinate(To) )
    {
        std::cout << "invalid coordinates\n";
    }

    MakeMove(From, To);
//    MakeMove(Coordinate(1, 'a'), Coordinate(2, 'a'));
//    MakeMove(Coordinate(2, 'a'), Coordinate(1, 'a'));

//    if((IsCheck() && IsCheckmate()) || IsStalemate())
//    {
//        exit(0);
//    }
}
