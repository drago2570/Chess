#pragma once
#include "coordinate.h"
#include "info.h"
#include <iostream>
#include <vector>

// https://www.ideone.com/USljB4
class IFigure
{
protected:
    Info m_info;
    std::vector<Coordinate> m_avaliableMoves;
public:
    explicit IFigure(int x, char y, Color color, Type type)
        : m_info{x, y, color, type}
    {
//        std::cout << "IFigure type " << (int)m_info.type << " color " << (int)m_info.color
//                  << " coordinate (" << m_info.coordinate.x << "; " << m_info.coordinate.y << ")\n";

    }
    explicit IFigure()
        : m_info{}
    {}
    explicit IFigure(Info&& info)
        : m_info{std::move(info)}
    {}
    virtual void UpdateCoordinate(Coordinate To) = 0;
    virtual std::vector<Coordinate> GeneratePossibleMoves() = 0;
    virtual bool CheckMove(Coordinate) {return false;};
    Coordinate getCoordinate() const;
    const Info& GetInfo() const;

    virtual ~IFigure() {} //{std::cout << "~IFigure()\n";}
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
    {
//        std::cout << "Pawn type " << (int)m_info.type << " color " << (int)m_info.color
//                  << " coordinate (" << m_info.coordinate.x << "; " << m_info.coordinate.y << ")\n";

    }
    Pawn(Info&& info)
        : IFigure{std::move(info)}
    {}
    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;
    std::vector<Coordinate> GeneratePossibleMoves() override;
    ~Pawn(){} // {std::cout << "~Pawn()\n";}
};


class King final : public IFigure
{
    bool m_isFirstMove;
public:
    King(int x, char y, Color color)
        : IFigure(x, y, color, Type::King),
          m_isFirstMove{false}
    {}
    King(Info&& info)
        : IFigure{std::move(info)}
    {}
    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;
    std::vector<Coordinate> GeneratePossibleMoves() override;
    ~King() {}
    bool isFirstMove() const;
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
    bool CheckMove(Coordinate newCoordinate) override;
    std::vector<Coordinate> GeneratePossibleMoves() override;
    ~Knight() {}
};

class Bishop : public virtual IFigure
{
public:
    Bishop(int x, char y, Color color)
        : IFigure(x, y,color, Type::Bishop)
    {
        std::cout << "Bishop1\n";
    }
    Bishop(Info&& info)
        : IFigure{std::move(info)}
    {}

    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;
    std::vector<Coordinate> GeneratePossibleMoves() override;
    virtual ~Bishop() {}
};

class Rook : public virtual IFigure
{
    bool m_isFirstMove;
public:
    Rook(int x, char y, Color color)
        : IFigure(x, y, color, Type::Rook),
          m_isFirstMove{false}
    {
        std::cout << "Rook1\n";
    }
    Rook(Info&& info)
        : IFigure{std::move(info)}
    {}

    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;
    std::vector<Coordinate> GeneratePossibleMoves() override;
    virtual ~Rook() {}
    bool isFirstMove() const;
};

class Queen final : public Bishop, public Rook
{
public:
    Queen(int x, char y, Color color)
        : IFigure(x, y, color, Type::Queen),
          Bishop(x, y, color),
          Rook(x, y, color)
    {}
//    Queen(Info&& info)
//        : IFigure{std::move(info)}
//    {}
    void UpdateCoordinate(Coordinate To) override;
    bool CheckMove(Coordinate newCoordinate) override;
    std::vector<Coordinate> GeneratePossibleMoves() override;
    virtual ~Queen() {}
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

    Empty(Coordinate coordinate)
        : IFigure(coordinate.x, coordinate.y, Color::None, Type::Empty)
    {}
    void UpdateCoordinate(Coordinate To) override;
    std::vector<Coordinate> GeneratePossibleMoves() override {return {};}

    ~Empty(){} // {std::cout << "~Empty()\n";}
};
