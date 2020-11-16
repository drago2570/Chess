#pragma once
#include <tuple>
#include "coordinate.h"

using LinesDots = std::tuple<Coordinate, Coordinate, Coordinate, Coordinate>;

LinesDots Diagonals(Coordinate startPoint)
{
    Coordinate A(0,0);
    Coordinate B(7,7);
    Coordinate C = startPoint;
    auto [x1, y1] = Coordinate::GetXY(A);
    auto [x2, y2] = Coordinate::GetXY(B);
    auto [x3, y3] = Coordinate::GetXY(C);
    int D = (x3-x1) * (y2-y1) - (y3-y1) * (x2-x1);
    D = D/7;
    auto startLeft = D < 0 ? Coordinate(0, -1*D) : Coordinate(D, 0);
    auto endLeft = D < 0 ? Coordinate(7 + D, 7) : Coordinate(7, 7-D);


    Coordinate K(0,7);
    Coordinate L(7,0);
    Coordinate M = startPoint;
    auto [x11, y11] = Coordinate::GetXY(K);
    auto [x12, y12] = Coordinate::GetXY(L);
    auto [x13, y13] = Coordinate::GetXY(M);
    int N = (x13-x11) * (y12-y11) - (y13-y11) * (x12-x11);
    N = N/7;
    auto startRight = N < 0 ? Coordinate(-1*N, 7): Coordinate(0, 7-N);
    auto endRight = N < 0 ? Coordinate(7, -1*N) : Coordinate(7-N, 0);

    return {startLeft, endLeft, startRight, endRight};
}

LinesDots Lines(Coordinate startPoint)
{
    return {Coordinate(startPoint.x, 0), Coordinate(startPoint.x, 7),
                Coordinate(0, startPoint.y), Coordinate(7, startPoint.y)};
}
