#include "board.h"
#include <algorithm>
#include <iostream>

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

void Board::UpdateBoard(Coordinate From, Coordinate To)
{
    auto [x1, y1]= Coordinate::GetXY(From);
    auto [x2, y2] = Coordinate::GetXY(To);
//    std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
//    std::cout << (m_state[x1][y1].figure->GetInfo().type == Type::Pawn) << " " << (m_state[x2][y2].figure->GetInfo().type == Type::Pawn) <<std::endl;

    std::swap(m_state[x1][y1].figure, m_state[x2][y2].figure);
}

void Board::DrawBoard() const noexcept
{
    for(int i = 0; i < 8; ++i)
    {
        std::cout << "#########################\n";
        std::cout << "|";
        for(int j = 0; j < 8; ++j)
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
