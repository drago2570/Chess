#include "chess.h"
#include <iostream>
#include <cstdlib>

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
            && m_board.VerificationMove(From, To))
    {
        m_players[(int)m_currentPlayer].UpdateCoordinateForPlayer(From, To);

        if(IsMoveSafe())
        {
            if (/*cellFrom.figure->GetInfo().color != cellTo.figure->GetInfo().color
                    && */cellTo.figure->GetInfo().type != Type::Empty)
            {
                m_board.MakeCellEmpty(To);
            }

            cellFrom.figure->UpdateCoordinate(To);
            m_board.UpdateBoard(From, To);
        }
        else
        {
            m_players[(int)m_currentPlayer].UpdateCoordinateForPlayer(To, From);
        }

        m_currentPlayer = !m_currentPlayer;
    }
    else
    {
        std::cout << "invalid move\n";
    }
    ClearTerminal();
    m_board.DrawBoard();
}

// TODO
bool Chess::IsMoveSafe() const
{
    auto kingCoordinate = m_players[static_cast<int>(m_currentPlayer)].kingCoordinate();
    decltype(auto) threatFigures = m_players[static_cast<int>(!m_currentPlayer)].allAvaliableFigures();
    // Update board before check
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

void Chess::ClearTerminal() const
{
#ifdef __unix__
    std::system("clear");
#elif defined(_WIN32)
    std::system("cls");
#endif
}

// TODO
bool Chess::IsCheckmate(Coordinate coordinate)
{
    Coordinate kingCoordinate = m_players[(int)!m_currentPlayer].kingCoordinate();
    const Cell& kingCell = m_board.GetCell(kingCoordinate);

    // if king can take threat figure by itself
    if (kingCell.figure->CheckMove(coordinate)
            && IsMoveSafe())
        return false;
    // check if king can move under danger
    for(auto& move : kingCell.figure->GeneratePossibleMoves())
    {
        if(kingCell.figure->CheckMove(move)
                && m_board.VerificationMove(kingCoordinate, move)
                && IsMoveSafe())
        {
            return false;
        }
    }

    auto threatFigures = m_players[(int)!m_currentPlayer].allAvaliableFigures();


    return true;
}

bool Chess::IsCastlingPosible(Coordinate From, Coordinate To)
{
    decltype(auto) cellFrom = m_board.GetCell(From);
    decltype(auto) cellTo = m_board.GetCell(To);

    if( (cellFrom.figure->GetInfo().type == Type::King && !dynamic_cast<King*>(cellFrom.figure.get())->isFirstMove())
            && (cellTo.figure->GetInfo().type == Type::Rook && !dynamic_cast<Rook*>(cellTo.figure.get())->isFirstMove()) )
    {
        return true;
    }
    // TODO: Check line from king to Rook
    return false;
}

bool Chess::IsStalemate()
{
    for(auto& figureCoordinate : m_players[(int)m_currentPlayer].allAvaliableFigures() )
        if(m_board.GetCell(figureCoordinate).figure->GeneratePossibleMoves().size() != 0)
            return false;

    return true;
}

void Chess::run()
{
    m_board.DrawBoard();

    while(true)
    {
        auto[From, To] = ReadFromUser();

        if( !Coordinate::ValidateCoordinate(From)
            || !Coordinate::ValidateCoordinate(To) )
        {
            std::cout << "invalid coordinates\n";
        }

        if(m_board.GetCell(From).figure->GetInfo().color == m_currentPlayer)
        {
            MakeMove(From, To);
            // TODO
            if((IsCheck(To) && IsCheckmate(To)))
            {
                exit(0);
            }
            else
            {
                IsStalemate();
            }
        }
    }
}
