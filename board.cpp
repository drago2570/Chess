#include "board.h"
#include <algorithm>
#include <iostream>

bool Board::CheckDiagonal(Coordinate From, Coordinate To) const
{
    int x1 = Coordinate::GetX(From);
    int x2 = Coordinate::GetX(To);

//    auto startPoint = From.x < To.x ?
//                To.y < From.y ? From
//                                : To
//              : To.y < From.y ? To
//                              : From;
    Coordinate startPoint;

    if(From.x < To.x)
    {
        if(To.y < From.y) startPoint = From;
        else startPoint = To;
    }
    else
    {
        if(To.y < From.y) startPoint = To;
        else startPoint = From;
    }


    for(int i = startPoint.x, j = Coordinate::GetY(startPoint), minus = 0; i < abs(x1-x2); ++i, ++j, ++minus)
        if(GetCell(From).figure->GetInfo().coordinate != GetCell(i-minus, j-minus).figure->GetInfo().coordinate &&
            GetCell(i-minus, j-minus).figure->GetInfo().type != Type::Empty)
            return false;

    return true;
}

bool Board::CheckLine(Coordinate From, Coordinate To) const
{
    auto [x1,y1] = Coordinate::GetXY(From);
    auto [x2,y2] = Coordinate::GetXY(To);

    if(abs(y1-y2) == 0)
    {
        auto vertRes = std::min(x1, x2);
        for(int i = vertRes; i <= vertRes + (abs(x1-x2)); ++i)
            if(GetCell(From).figure->GetInfo().coordinate != GetCell(i, y1).figure->GetInfo().coordinate &&
                    GetCell(i, y1).figure->GetInfo().type != Type::Empty)
                return false;
    }
    else if(abs(x1-x2) == 0)
    {
        auto horRes = std::min(y1, y2);
        for(int i = horRes; i <= horRes + (abs(y1-y2)); ++i)
            if(GetCell(From).figure->GetInfo().coordinate != GetCell(i, y1).figure->GetInfo().coordinate &&
                    GetCell(x1, i).figure->GetInfo().type != Type::Empty)
                return false;
    }

    return true;
}

Board &Board::instance()
{
    static Board inst;
    return inst;
}

const Cell& Board::GetCell(Coordinate coordinate) const
{
    auto [x,y] = Coordinate::GetXY(coordinate);
    return m_state[x][y];
}

const Cell &Board::GetCell(int x, int y) const
{
    return m_state[x][y];
}

void Board::UpdateBoard(Coordinate From, Coordinate To)
{
    auto [x1, y1]= Coordinate::GetXY(From);
    auto [x2, y2] = Coordinate::GetXY(To);
    std::swap(m_state[x1][y1].figure, m_state[x2][y2].figure);
}

void Board::DrawBoard() const noexcept
{
    for(int i = 0; i < ROWS; ++i)
    {
        std::cout << "#########################\n";
        std::cout << "|";
        for(int j = 0; j < COLUMNS; ++j)
        {
            std::string data = "";
            if(m_state[i][j].figure->GetInfo().color == Color::White)
            {
                data += "W";
            }
            else if (m_state[i][j].figure->GetInfo().color == Color::Black)
            {
                data += "B";
            }

            switch(m_state[i][j].figure->GetInfo().type)
            {
                case Type::King:
                    data += "K";
                break;
                case Type::Queen:
                    data += "Q";
                break;
                case Type::Knight:
                    data += "N";
                break;
                case Type::Bishop:
                    data += "B";
                break;
                case Type::Pawn:
                    data += "P";
                break;
                case Type::Empty:
                   data += "  ";
                 break;
                default:
                break;
            }
            std::cout << data + "|";
        }
        std::cout << std::endl;
    }
}

bool Board::VerificationMove(Coordinate From, Coordinate To) const noexcept
{
    std::cout << CheckDiagonal(Coordinate(0, 'a'), Coordinate(2, 'c')) << std::endl;
    std::cout << CheckDiagonal(Coordinate(0, 'e'), Coordinate(2, 'c')) << std::endl;
    if(GetCell(From).figure->GetInfo().color == GetCell(To).figure->GetInfo().color)
    {
        return false;
    }

    switch (GetCell(From).figure->GetInfo().type)
    {
    case Type::Bishop:{}
    case Type::King: {}
    case Type::Queen: {}
    case Type::Rook: {}

    case Type::Pawn:
    case Type::Knight:
    case Type::Empty: {break;}

    default: {break;}
    }

    return true;
}
