#pragma once
#include "coordinate.h"
#include "info.h"
class IFigure
{
    Coordinate m_coordinate;
    Info m_info;
public:
    virtual void Move(Coordinate From, Coordinate To) = 0;
    explicit IFigure(short int x, char y)
        :m_coordinate{Coordinate(x, y)}
    {}

    virtual ~IFigure();
};

class Pawn : public IFigure
{
public:
    Pawn(short int x, char y) : IFigure(x, y)
    {}
    void Move(Coordinate From, Coordinate To) override;
};


class King : public IFigure
{
public:
    King(short int x, char y) : IFigure(x, y)
    {}
};

class Queen : public IFigure
{
public:
    Queen(short int x, char y) : IFigure(x, y)
    {}
};

class Bishop : public IFigure
{
public:
    Bishop(short int x, char y) : IFigure(x, y)
    {}
};

class Knight : public IFigure
{
public:
    Knight(short int x, char y) : IFigure(x, y)
    {}
};

class Rook : public IFigure
{
public:
    Rook(short int x, char y) : IFigure(x, y)
    {}
};

class Empty : public IFigure
{
    Empty(short int x, char y) : IFigure(x, y)
    {}
};
