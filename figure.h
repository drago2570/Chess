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
    explicit IFigure(Info&& info)
        : m_info{std::move(info)}
    {}
    virtual void UpdateCoordinate(Coordinate To) = 0;
    virtual bool CheckMove(Coordinate) {return false;};
    Coordinate getCoordinate() const;
    const Info& GetInfo() const;
    void SetInfo(Info&);

    virtual ~IFigure() {}
};

class Pawn final : public IFigure
{
    bool isFirstMove;
    bool isFirstLongMove;
public:
    Pawn(int x, char y, Color color)
        : IFigure(x, y, color, Type::Pawn),
          isFirstMove{false},
          isFirstLongMove{false}
    {}
    Pawn(Info&& info)
        : IFigure{std::move(info)}
    {}
    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;;
    ~Pawn(){}
};


class King final : public IFigure
{
    bool isFirstMove;
public:
    King(int x, char y, Color color)
        : IFigure(x, y, color, Type::King),
          isFirstMove{false}
    {}
    King(Info&& info)
        : IFigure{std::move(info)}
    {}
    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;;
    ~King() {}
};

class Queen final : public IFigure
{
public:
    Queen(int x, char y, Color color)
        : IFigure(x, y, color, Type::Queen)
    {}
    Queen(Info&& info)
        : IFigure{std::move(info)}
    {}
    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;;
    ~Queen() {}
};

class Bishop final : public IFigure
{
public:
    Bishop(int x, char y, Color color)
        : IFigure(x, y,color, Type::Bishop)
    {}
    Bishop(Info&& info)
        : IFigure{std::move(info)}
    {}
    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;;
    ~Bishop() {}
};

class Knight final : public IFigure
{
public:
    Knight(int x, char y, Color color)
        : IFigure(x, y, color, Type::Knight)
    {}
    Knight(Info&& info)
        : IFigure{std::move(info)}
    {}
    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;;
    ~Knight() {}
};

class Rook final : public IFigure
{
    bool isFirstMove;
public:
    Rook(int x, char y, Color color)
        : IFigure(x, y, color, Type::Rook),
          isFirstMove{false}
    {}
    Rook(Info&& info)
        : IFigure{std::move(info)}
    {}
    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;;
    ~Rook() {}
};

class Empty final : public IFigure
{
public:
    Empty() : IFigure() {}
    Empty(int x, char y)
        : IFigure(x, y, Color::None, Type::Empty)
    {}
    Empty(Info&& info)
        : IFigure{std::move(info)}
    {}
    void UpdateCoordinate(Coordinate To) override;

    ~Empty() {}
};
