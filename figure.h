#pragma once
#include "coordinate.h"
#include "info.h"
// https://www.ideone.com/USljB4
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
    virtual void UpdateCoordinate(Coordinate To) = 0;
    virtual bool CheckMove(Coordinate newCoordinate) {newCoordinate = {}; return false;};
    Coordinate getCoordinate() const;
    Info GetInfo() const;

    virtual ~IFigure() {}
};

class Pawn final : public IFigure
{

public:
    Pawn(int x, char y, Color color) : IFigure(x, y, color, Type::Pawn)
    {}
    void UpdateCoordinate(Coordinate To) final override;
    virtual bool CheckMove(Coordinate newCoordinate) override;;
    ~Pawn(){}
};


class King final : public IFigure
{

public:
    King(int x, char y, Color color) : IFigure(x, y, color, Type::King)
    {}
    void UpdateCoordinate(Coordinate To) final override;
    virtual bool CheckMove(Coordinate newCoordinate) override;;
    ~King() {}
};

class Queen final : public IFigure
{
public:
    Queen(int x, char y, Color color) : IFigure(x, y, color, Type::Queen)
    {}
    void UpdateCoordinate(Coordinate To) final override;
    virtual bool CheckMove(Coordinate newCoordinate) override;;
    ~Queen() {}
};

class Bishop final : public IFigure
{
public:
    Bishop(int x, char y, Color color) : IFigure(x, y,color, Type::Bishop)
    {}
    void UpdateCoordinate(Coordinate To) final override;
    virtual bool CheckMove(Coordinate newCoordinate) override;;
    ~Bishop() {}
};

class Knight final : public IFigure
{
public:
    Knight(int x, char y, Color color) : IFigure(x, y, color, Type::Knight)
    {}
    void UpdateCoordinate(Coordinate To) final override;
    virtual bool CheckMove(Coordinate newCoordinate) override;;
    ~Knight() {}
};

class Rook final : public IFigure
{
public:
    Rook(int x, char y, Color color) : IFigure(x, y, color, Type::Rook)
    {}
    void UpdateCoordinate(Coordinate To) final override;
    virtual bool CheckMove(Coordinate newCoordinate) override;;
    ~Rook() {}
};

class Empty final : public IFigure
{
public:
    Empty() : IFigure() {}
    Empty(int x, char y) : IFigure(x, y, Color::None, Type::Empty)
    {}
    void UpdateCoordinate(Coordinate To) final override;

    ~Empty() {}
};
