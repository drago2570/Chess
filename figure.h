#pragma once
#include "coordinate.h"
#include "info.h"

class IFigure
{
protected:
    Info m_info;
public:
    explicit IFigure(int x, char y, Color color, Type type)
        : m_info{x, y, color, type}
    {}
    explicit IFigure()
        : m_info{}
    {}
    virtual void Move(Coordinate To) = 0;

    Coordinate getCoordinate() const;
    Info GetInfo() const;

    virtual ~IFigure() {}
};

class Pawn final : public IFigure
{
public:
    Pawn(int x, char y, Color color) : IFigure(x, y, color, Type::Pawn)
    {}
    void Move(Coordinate To) final override;

    ~Pawn(){}
};


class King final : public IFigure
{
public:
    King(int x, char y, Color color) : IFigure(x, y, color, Type::King)
    {}
    void Move(Coordinate To) final override;
    ~King() {}
};

class Queen final : public IFigure
{
public:
    Queen(int x, char y, Color color) : IFigure(x, y, color, Type::Queen)
    {}
    void Move(Coordinate To) final override;
    ~Queen() {}
};

class Bishop final : public IFigure
{
public:
    Bishop(int x, char y, Color color) : IFigure(x, y,color, Type::Bishop)
    {}
    void Move(Coordinate To) final override;
    ~Bishop() {}
};

class Knight final : public IFigure
{
public:
    Knight(int x, char y, Color color) : IFigure(x, y, color, Type::Knight)
    {}
    void Move(Coordinate To) final override;
    ~Knight() {}
};

class Rook final : public IFigure
{
public:
    Rook(int x, char y, Color color) : IFigure(x, y, color, Type::Rook)
    {}
    void Move(Coordinate To) final override;
    ~Rook() {}
};

class Empty final : public IFigure
{
public:
    Empty() : IFigure() {}
    Empty(int x, char y) : IFigure(x, y, Color::None, Type::Empty)
    {}
    void Move(Coordinate To) final override;

    ~Empty() {}
};
