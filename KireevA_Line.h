#pragma once
#include "KireevA_Plane.h"
namespace KireevA
{
    class Line
    {
    public:
        Line(){}
        Line(const Plane & p1, const Plane & p2);
        Line(const Vector & v, const Point & p) : m_dir(v), m_p(p) {}
        Vector GetDir() const
        {
            return m_dir;
        }
        Point GetPoint() const
        {
            return m_p;
        }
        Point GetPoint(double parameter) const
        {
            return Point(m_p + m_dir * parameter);
        }
        virtual bool Contains(const Point & p) const;
        double GetParameter(const Point & p) const;
        std::vector<Point> Intersect(const Line& l) const;
        std::vector<Point> Distance(const Line& l) const;
    private:
        Vector m_dir;
        Point m_p;
    };
}