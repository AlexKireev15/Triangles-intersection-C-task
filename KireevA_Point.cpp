#include "KireevA_Point.h"
#include "KireevA_Utils.h"

namespace KireevA
{
    Vector operator-(const Point & p1, const Point & p2)
    {
        return Vector(p1.m_x - p2.m_x, p1.m_y - p2.m_y, p1.m_z - p2.m_z);
    }

    Point operator/(Point p, double div)
    {
        p.m_x /= div;
        p.m_y /= div;
        p.m_z /= div;
        return p;
    }
    Point operator+(Point p, const Vector& v)
    {
        p.m_x += v.GetX();
        p.m_y += v.GetY();
        p.m_z += v.GetZ();
        return p;
    }

    bool operator==(const Point & p1, const Point & p2)
    {
        return eq(p1.m_x, p2.m_x) && eq(p1.m_y, p2.m_y) && eq(p1.m_z, p2.m_z);
    }

    bool operator!=(const Point & p1, const Point & p2)
    {
        return !(p1 == p2);
    }
}