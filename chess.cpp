#include "chess.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

Chess::Chess()
    : m_board(Board::instance()),
      m_players{Player{Color::White}, Player{Color::Black}},
      m_currentPlayer{Color::Black}
{}

Color operator!(Color color)
{
    return color == Color::Black ? Color::White : Color::Black;
}

void Chess::Castilng(Coordinate From, Coordinate To) // From - king, To - rook
{
    const Cell& cellFrom = m_board.GetCell(From); // king
    const Cell& cellTo = m_board.GetCell(To); // rook

    if(cellFrom.figure->GetInfo().color == Color::White)
    {
        if(cellFrom.figure->getCoordinate().y < cellTo.figure->getCoordinate().y)
        {
            cellFrom.figure->UpdateCoordinate(Coordinate(7, 'c')); // king
            m_board.UpdateBoard(From, Coordinate(7, 'c'));
            cellTo.figure->UpdateCoordinate(Coordinate(7, 'd')); // rook
            m_board.UpdateBoard(From, Coordinate(7, 'd'));
        }
        else
        {
            cellFrom.figure->UpdateCoordinate(Coordinate(7, 'g')); // king
            m_board.UpdateBoard(From, Coordinate(7, 'g'));
            cellTo.figure->UpdateCoordinate(Coordinate(7, 'f')); // rook
            m_board.UpdateBoard(From, Coordinate(7, 'f'));
        }
    }
    else if(cellFrom.figure->GetInfo().color == Color::Black)
    {
        if(cellFrom.figure->getCoordinate().y < cellTo.figure->getCoordinate().y)
        {
            cellFrom.figure->UpdateCoordinate(Coordinate(0, 'c')); // king
            m_board.UpdateBoard(From, Coordinate(0, 'c'));
            cellTo.figure->UpdateCoordinate(Coordinate(0, 'd')); // rook
            m_board.UpdateBoard(From, Coordinate(0, 'd'));
        }
        else
        {
            cellFrom.figure->UpdateCoordinate(Coordinate(0, 'g')); // king
            m_board.UpdateBoard(From, Coordinate(0, 'g'));
            cellTo.figure->UpdateCoordinate(Coordinate(0, 'f')); // rook
            m_board.UpdateBoard(From, Coordinate(0, 'f'));
        }
    }
}

void Chess::MakeMove(Coordinate From, Coordinate To)
{
    const Cell& cellFrom = m_board.GetCell(From);
    const Cell& cellTo = m_board.GetCell(To);

    if(cellFrom.figure->CheckMove(To)
            && m_board.VerificationMove(From, To))
    {
        if(IsMoveSafe(From, To))
        {
            if (/*cellFrom.figure->GetInfo().color != cellTo.figure->GetInfo().color
                    && */cellTo.figure->GetInfo().type != Type::Empty)
            {
                m_board.MakeCellEmpty(To);
            }

            cellFrom.figure->UpdateCoordinate(To);
            m_board.UpdateBoard(From, To);
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

bool Chess::IsMoveSafe(Coordinate From, Coordinate To)
{
    std::size_t pos = m_players[(int)m_currentPlayer].UpdateCoordinateForPlayer(From, To);
    auto kingCoordinate = m_players[static_cast<int>(m_currentPlayer)].kingCoordinate();
    decltype(auto) threatFigures = m_players[static_cast<int>(!m_currentPlayer)].allAvaliableFigures();

    for(auto& coordinate : threatFigures)
    {
        const auto& figure = m_board.GetCell(coordinate);
        if(figure.figure->CheckMove(kingCoordinate))
        {
            m_players[(int)m_currentPlayer].UpdateCoordinateForPlayer(pos, From);
            return false;
        }
    }

    m_players[(int)m_currentPlayer].UpdateCoordinateForPlayer(pos, From);
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
bool Chess::IsCheckmate(Coordinate) // coordinate - is coordinate of thread figure
{
    // EXAMPLE: White
    Coordinate kingCoordinate = m_players[(int)m_currentPlayer].kingCoordinate(); // get white king
    const Cell& kingCell = m_board.GetCell(kingCoordinate);

    // check if king can move under danger
    for(auto& move : kingCell.figure->GeneratePossibleMoves())
    {
        if(kingCell.figure->CheckMove(move)
                && m_board.VerificationMove(kingCoordinate, move)
                && IsMoveSafe(kingCoordinate, move))
        {
            return false;
        }
    }

    // count threat figures
    std::vector<Coordinate> threatFigure;
    for(const auto& coordinate : m_players[(int)!m_currentPlayer].allAvaliableFigures()) // chech how much black figure threaten
    {
        if(const Cell& cell = m_board.GetCell(coordinate); cell.figure->CheckMove(kingCoordinate))
        {
            threatFigure.push_back(coordinate);
        }
    }

    if(threatFigure.size() == 1)
    {
        for(const auto& coordinate : m_players[(int)m_currentPlayer].allAvaliableFigures()) // get all white figures
        {
            if(const Cell& cell = m_board.GetCell(coordinate); cell.figure->CheckMove(kingCoordinate) // chech if white figures can take threat figure
                    && m_board.VerificationMove(coordinate, threatFigure[0])
                    && IsMoveSafe(coordinate, threatFigure[0]))
            {
                return false;
            }
        }

        std::vector<Coordinate> threatFigurePossibleMoves = m_board.GetCell(threatFigure[0]).figure->GeneratePossibleMoves(); // get all threat figure moves
        for(const auto& coordinate : m_players[(int)m_currentPlayer].allAvaliableFigures())
        {
            std::vector<Coordinate> possibleMoves = m_board.GetCell(coordinate).figure->GeneratePossibleMoves();
            for(Coordinate  move : possibleMoves)
            {
                // chech if our figures can defend king
                auto it = std::find(begin(threatFigurePossibleMoves), end(threatFigurePossibleMoves), move);
                if(it != end(threatFigurePossibleMoves)
                        && m_board.VerificationMove(move, *it)
                        && IsMoveSafe(move, *it))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Chess::IsCastlingPosible(Coordinate From, Coordinate To)
{
    decltype(auto) cellFrom = m_board.GetCell(From);
    decltype(auto) cellTo = m_board.GetCell(To);

    if( (cellFrom.figure->GetInfo().type == Type::King && !dynamic_cast<King*>(cellFrom.figure.get())->isFirstMove())
            && (cellTo.figure->GetInfo().type == Type::Rook && !dynamic_cast<Rook*>(cellTo.figure.get())->isFirstMove()) )
    {
        auto opponentFiguresCoordinate = m_players[(int)m_currentPlayer].allAvaliableFigures();

        std::vector<Coordinate> castlingWay = { m_players[(int)m_currentPlayer].kingCoordinate()};
        int raw = cellFrom.figure->GetInfo().color == Color::White ? 7 : 0;

        if(cellFrom.figure->getCoordinate().y < cellTo.figure->getCoordinate().y)
        {
            castlingWay.emplace_back(raw, 'c');
            castlingWay.emplace_back(raw, 'd');
        }
        else
        {
            castlingWay.emplace_back(raw, 'f');
            castlingWay.emplace_back(raw, 'g');
        }

        for(const auto& castlingCell : castlingWay)
        {
            for(const auto& coordinate : opponentFiguresCoordinate)
            {
                if( const Cell& cell = m_board.GetCell(coordinate); cell.figure->CheckMove(castlingCell) )
                {
                    return false;
                }
            }
        }
    }

    return false;
}

bool Chess::IsStalemate()
{
    for(auto& figureCoordinate : m_players[(int)m_currentPlayer].allAvaliableFigures())
        if(m_board.GetCell(figureCoordinate).figure->GeneratePossibleMoves().empty())
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
