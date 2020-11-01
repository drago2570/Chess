#pragma once
#include "coordinate.h"
#include "info.h"

class IFigure
{
    Coordinate m_coordinate;
    Info m_info;
public:
    virtual void Move(Coordinate From, Coordinate To) = 0;
    explicit IFigure(short int x, char y, Info info = {})
        :m_coordinate{Coordinate(x, y)},
         m_info{info}
    {}

    virtual ~IFigure();
};

class Pawn : public IFigure
{
public:
    Pawn(short int x, char y, Color color) : IFigure(x, y, Info(color, Type::Pawn))
    {}
    void Move(Coordinate From, Coordinate To) override;
};


class King : public IFigure
{
public:
    King(short int x, char y, Color color) : IFigure(x, y, Info(color, Type::King))
    {}
};

class Queen : public IFigure
{
public:
    Queen(short int x, char y, Color color) : IFigure(x, y, Info(color, Type::Queen))
    {}
};

class Bishop : public IFigure
{
public:
    Bishop(short int x, char y, Color color) : IFigure(x, y, Info(color, Type::Bishop))
    {}
};

class Knight : public IFigure
{
public:
    Knight(short int x, char y, Color color) : IFigure(x, y, Info(color, Type::Knight))
    {}
};

class Rook : public IFigure
{
public:
    Rook(short int x, char y, Color color) : IFigure(x, y, Info(color, Type::Rook))
    {}
};

class Empty : public IFigure
{
    Empty(short int x, char y, Color color = Color::None) : IFigure(x, y)
    {}
};
