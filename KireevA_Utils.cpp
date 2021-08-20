#include "KireevA_Utils.h"

#include <algorithm>

namespace KireevA
{
    template<typename T>
    bool TryCastTo<T>(Triangle t, T & o)
    {
        return false;
    }

    template<>
    bool TryCastTo<Point>(Triangle T, Point & p)
    {
        if (T.GetVert(0) == T.GetVert(1) && T.GetVert(0) == T.GetVert(2))
        {
            p = T.GetVert(0);
            return true;
        }
        return false;
    }

    template<>
    bool TryCastTo<Segment>(Triangle T, Segment & s)
    {
        Point v1 = T.GetVert(0);
        Point v2;
        Point v3;
        if (T.GetVert(1) != T.GetVert(0))
        {
            v2 = T.GetVert(1);
            v3 = T.GetVert(2);
        }
        else if (T.GetVert(2) != T.GetVert(0))
        {
            v2 = T.GetVert(2);
            v3 = T.GetVert(1);
        }
        else
        {
            return false;
        }

        Line l(v2 - v1, v1);

        double t1 = l.GetParameter(v1),
               t2 = l.GetParameter(v2),
               t3 = l.GetParameter(v3);

        double maxParameter = std::max({ t1, t2, t3 });
        double minParameter = std::min({ t1, t2, t3 });

        s = Segment(l, l.GetPoint(maxParameter), l.GetPoint(minParameter));

        return true;
    }

    Vector Normalize(const Vector & v)
    {
        return v / v.GetAbs();
    }

    Point Project(const Line & line, const Point & point)
    {
        Point res = line.GetPoint();
        Vector v = point - line.GetPoint();
        Vector dirNorm = Normalize(line.GetDir());
        v = dirNorm * v.ScalarProduct(dirNorm);
        return res + v;
    }

    std::vector<Point> Project(const Line & line, const std::vector<Point>& points)
    {
        std::vector<Point> res;

        Vector dirNorm = Normalize(line.GetDir());
        Point p0 = line.GetPoint();
        for (auto it = points.begin(); it != points.end(); ++it)
        {
            res.push_back(p0 + dirNorm * (*it - p0).ScalarProduct(dirNorm));
        }

        return res;
    }

    bool IsNullVector(const Vector & v)
    {
        return eq0(v.GetX()) && eq0(v.GetY()) && eq0(v.GetZ());
    }

    bool eq(const double & a, const double & b)
    {
        return abs(a - b) < Eps;
    }

    bool eq0(const double & a)
    {
        return eq(a, 0.0);
    }

    bool IsPointInsidePoints(const Point& vert, const std::vector<Point>& verts, const Plane& p)
    {
        auto shift = [](size_t idx, size_t shift, size_t size)
        {
            return (idx + shift) % size;
        };

        int prevSign = 0;

        for (size_t idx = 0u; idx < verts.size(); ++idx)
        {
            Point p1 = verts[idx], p2 = verts[shift(idx, 1u, verts.size())];
            Vector v1 = p2 - p1;
            Vector v2 = vert - p1;

            int sign = sgn(v1.CrossProduct(v2).ScalarProduct(p.GetNormal()));
            if (sign != 0)
            {
                if (prevSign != 0 && sign != prevSign)
                {
                    return false;
                }
                prevSign = sign;
            }

        }
        return true;
    }
}