#pragma once
#include "KireevA_Point.h"
#include "KireevA_Plane.h"
#include "KireevA_Line.h"
#include "KireevA_Triangle.h"
#include "KireevA_Segment.h"

#include <array>
#include <vector>

namespace KireevA
{
    static const double Eps = 1e-9;
    template <typename T> inline constexpr 
    int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }
    bool eq(const double & a, const double & b);
    bool eq0(const double & a);
    Point Project(const Line & line, const Point & point);
    std::vector<Point> Project(const Line & line, const std::vector<Point> & points);
    Vector Normalize(const Vector & v);
    bool IsNullVector(const Vector& v);
    template <typename T> 
    bool TryCastTo(Triangle t, T & o);
    bool IsPointInsidePoints(const Point& vert, const std::vector<Point>& verts, const Plane& p);
}