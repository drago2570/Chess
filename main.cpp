#include <iostream>
#include "chess.h"
#include <array>

using std::unique_ptr;
using std::cout;
using std::endl;

enum class Enim_2
{
    En_1,
    En_2,
    En_3,
    En_4,
    En_5,
    En_6
};


struct FCoord
{
    int x, y;

    FCoord():
        x{-1}, y{-1}
    {}
    FCoord(int x, int y):
        x{x}, y{y}
    {}
};

struct TFigure
{
    int i;
    FCoord coord;
    Enim_2 en;
    TFigure(): i{0}, en{Enim_2::En_6}
    {
        cout << "T()\n";
    }

    TFigure(int v) : i{v}, coord{1, 2}, en{Enim_2::En_1}
    {
        cout << "T(int)\n";
    }

    virtual void foo() = 0;

    virtual ~TFigure() {}
};

struct TF : TFigure
{
    TF() : TFigure()
    {
        cout << "TF()\n";
    }

    TF(int v) : TFigure(v)
    {
        cout << "TF(int)\n";
    }

    virtual void foo() override
    {}

    ~TF() {}
};

struct TS : TFigure
{
    TS() : TFigure()
    {
        cout << "TS()\n";
    }

    TS(int v) : TFigure(v)
    {
        cout << "TS(int)\n";
    }

    virtual void foo() override
    {}

    ~TS() {}
};


struct Sell
{
	unique_ptr<TFigure> data;

	Sell() : data{new TF()}
	{
        cout << "S()\n";
    }

	Sell(unique_ptr<TFigure> val) :
	data {std::move(val)}
	{
        cout << "S(val)\n";
    }

    Sell& operator=(Sell&& other)
    {
        cout << "S& operator=(S&& other)\n";
        data = std::move(other.data);
        return *this;
    }

    void Data() const
    {
        cout << "i " << data->i << " coord (" << data->coord.x << "; " << data->coord.y << ") " << (int)data->en << endl;
    }
};

int main()
{
//    Sell s[2];
//    s[0].Data();
//    s[0] = Sell(unique_ptr<TFigure>(new TS(10)));
////    s[0] = S( unique_ptr<int>( new T ) );
//    s[0].Data();


//    std::array<Cell, 2> arr;
//    {
//    Cell* tmp = new Cell(std::unique_ptr<IFigure>(new Pawn(1, 'a', Color::Black)));
//    arr[0].figure = std::move(tmp->figure);
//    delete tmp;
//   }

//    std::cout << (int)arr[0].figure->GetInfo().type << std::endl;
//    Cell cell;
//    auto info = cell.figure->GetInfo();

//    std::cout << "type " << (int)info.type << " color " << (int)info.color << " coordinate (" << info.coordinate.x << "; " << info.coordinate.y << ")\n";

//    info = *cell.previewInfo;
//    std::cout << "type " << (int)info.type << " color " << (int)info.color << " coordinate (" << info.coordinate.x << "; " << info.coordinate.y << ")\n";





    Chess chess;
    std::cout << "size " << sizeof (chess) << std::endl;
    chess.run();

    return 0;
}
