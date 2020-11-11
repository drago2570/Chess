#include "board.h"
#include <algorithm>
#include <iostream>

Board::Board()
{
    m_state[0][0] = Cell(std::unique_ptr<IFigure>(new Rook(0, 'a', Color::Black)));
    m_state[0][1] = Cell(std::unique_ptr<IFigure>(new Knight(0, 'b', Color::Black)));
    m_state[0][2] = Cell(std::unique_ptr<IFigure>(new Bishop(0, 'c', Color::Black)));
    m_state[0][3] = Cell(std::unique_ptr<IFigure>(new Queen(0, 'd', Color::Black)));
    m_state[0][4] = Cell(std::unique_ptr<IFigure>(new King(0, 'e', Color::Black)));
    m_state[0][5] = Cell(std::unique_ptr<IFigure>(new Bishop(0, 'f', Color::Black)));
    m_state[0][6] = Cell(std::unique_ptr<IFigure>(new Knight(0, 'g', Color::Black)));
    m_state[0][7] = Cell(std::unique_ptr<IFigure>(new Rook(0, 'h', Color::Black)));

    char c = 'a';
    for(int i = 0; i < 8; ++i, ++c)
    {
        m_state[1][i] = Cell(std::unique_ptr<IFigure>(new Pawn(1, c, Color::Black)));
        m_state[6][i] = Cell(std::unique_ptr<IFigure>(new Pawn(7, c, Color::White)));
    }

    m_state[7][0] = Cell(std::unique_ptr<IFigure>(new Rook(7, 'a', Color::Black)));
    m_state[7][1] = Cell(std::unique_ptr<IFigure>(new Knight(7, 'b', Color::Black)));
    m_state[7][2] = Cell(std::unique_ptr<IFigure>(new Bishop(7, 'c', Color::Black)));
    m_state[7][3] = Cell(std::unique_ptr<IFigure>(new Queen(7, 'd', Color::Black)));
    m_state[7][4] = Cell(std::unique_ptr<IFigure>(new King(7, 'e', Color::Black)));
    m_state[7][5] = Cell(std::unique_ptr<IFigure>(new Bishop(7, 'f', Color::Black)));
    m_state[7][6] = Cell(std::unique_ptr<IFigure>(new Knight(7, 'g', Color::Black)));
    m_state[7][7] = Cell(std::unique_ptr<IFigure>(new Rook(7, 'h', Color::Black)));
}

bool Board::CheckDiagonal(Coordinate From, Coordinate To) const
{
    int x1 = Coordinate::GetX(From);
    int x2 = Coordinate::GetX(To);
    auto startPoint = std::max(From, To);

    std::cout << "startPoint " << startPoint.x << " " << startPoint.y << std::endl;
    for(int i = startPoint.x, coef = 1, j = Coordinate::GetY(startPoint), minus = 0; minus <= abs(x1-x2); ++minus)
    {
        std::cout << "minus " << minus << " index " << i-minus << " " << j-(minus*coef) << std::endl;
        if(GetCell(From).figure->getCoordinate() != GetCell(i-minus, j-(minus * coef)).figure->getCoordinate() &&
            GetCell(i-minus, j-(minus*coef)).figure->GetInfo().type != Type::Empty)
        {
            std::cout << "find figure\n";
            return false;
        }

        if( minus == 0 && ( (From.x < To.x && From.y > To.y)
                || (From.x > To.x && From.y < To.y) ) )
        {
            coef = -1;
            std::cout << "handle diagonal\n";
        }
    }

    std::cout << "end function\n";
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
            if(GetCell(From).figure->getCoordinate() != GetCell(i, y1).figure->getCoordinate() &&
                    GetCell(i, y1).figure->GetInfo().type != Type::Empty)
                return false;
    }
    else if(abs(x1-x2) == 0)
    {
        auto horRes = std::min(y1, y2);
        for(int i = horRes; i <= horRes + (abs(y1-y2)); ++i)
            if(GetCell(From).figure->getCoordinate() != GetCell(i, y1).figure->getCoordinate() &&
                    GetCell(x1, i).figure->GetInfo().type != Type::Empty)
                return false;
    }
    else {return false;}

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
    m_state[x1][y1].SetPreviewInfoByFigure();
    m_state[x2][y2].SetPreviewInfoByFigure();
}

void Board::DrawBoard() const
{
    std::cout << "    a  b  c  d  e  f  g  h\n";
    for(int i = 0; i < ROWS; ++i)
    {
        std::cout << "  #########################\n";
        std::cout << i << " |";
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
                case Type::Rook:
                    data += "R";
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
        std::cout << i << std::endl;
    }
    std::cout << "  #########################\n";
    std::cout << "   a  b  c  d  e  f  g  h\n";
}

bool Board::VerificationMove(Coordinate From, Coordinate To) const noexcept
{
    if(GetCell(From).figure->GetInfo().color == GetCell(To).figure->GetInfo().color)
    {
        return false;
    }
    // TODO: Check trying to take a figure;
    switch (GetCell(From).figure->GetInfo().type)
    {
    case Type::Bishop:{return CheckDiagonal(From, To);}
    case Type::Queen: {return (CheckLine(From, To) || CheckDiagonal(From, To));}
    case Type::Rook: {return CheckLine(From, To);}

    case Type::King:
    case Type::Pawn:
    case Type::Knight:
    case Type::Empty: {break;}

    default: {break;}
    }

    return true;
}

void Board::SetCoordinateForPreview(Coordinate newCoordinate)
{
    auto [x,y] = Coordinate::GetXY(newCoordinate);
    m_state[x][y].previewInfo.coordinate = newCoordinate;
}

void Board::Revert(Coordinate From)
{
    auto [x1, y1]= Coordinate::GetXY(From);
    m_state[x1][y1].SetPreviewInfoByFigure();
}

Board::~Board()
{}
