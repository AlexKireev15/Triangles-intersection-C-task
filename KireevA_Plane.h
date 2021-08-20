#pragma once
#include "KireevA_Vector.h"
#include "KireevA_Point.h"
#include <array>
#include <vector>

namespace KireevA
{
    class Plane
    {
    public:
        Plane()
        {
        }
        Plane(const Point & p1, const Point & p2, const Point & p3);
        Vector GetNormal() const
        {
            return m_normal;
        }
        double GetD() const
        {
            return -m_normal.GetX() * m_p.GetX() - m_normal.GetY() * m_p.GetY() - m_normal.GetZ() * m_p.GetZ();
        }
        double Distance(const Point & p) const;
        std::vector<double> Distances(const std::vector<Point>& points) const;
        double SgnDistance(const Point& p) const;
    private:
        Vector m_normal;
        Point m_p;
    };
};