#include "KireevA_Plane.h"
#include "KireevA_Utils.h"
#include <array>
namespace KireevA
{
    Plane::Plane(const Point & p1, const Point & p2, const Point & p3)
    {
        Vector v1 = p2 - p1;
        Vector v2 = p3 - p1;
        m_normal = v1.CrossProduct(v2);
        m_p = p1;
    }

    double Plane::Distance(const Point & p) const
    {
        double d0 = -m_normal.GetX() * m_p.GetX() - m_normal.GetY() * m_p.GetY() - m_normal.GetZ() * m_p.GetZ();
        double dist = m_normal.GetX() * p.GetX() + m_normal.GetY() * p.GetY() + m_normal.GetZ() * p.GetZ() + d0;
        return dist / m_normal.GetAbs();
    }
    
    std::vector<double> Plane::Distances(const std::vector<Point>& points) const
    {
        std::vector<double> distances;
        distances.resize(points.size());
        double d0 = -m_normal.GetX() * m_p.GetX() - m_normal.GetY() * m_p.GetY() - m_normal.GetZ() * m_p.GetZ();
        for (size_t idx = 0u; idx < points.size(); ++idx)
        {
            distances[idx] = m_normal.GetX() * points[idx].GetX() + m_normal.GetY() * points[idx].GetY() + m_normal.GetZ() * points[idx].GetZ() + d0;
            distances[idx] /= m_normal.GetAbs();
        }
        return distances;
    }

    double Plane::SgnDistance(const Point& p) const
    {
        double d0 = -m_normal.GetX() * m_p.GetX() - m_normal.GetY() * m_p.GetY() - m_normal.GetZ() * m_p.GetZ();
        double dist = m_normal.GetX() * p.GetX() + m_normal.GetY() * p.GetY() + m_normal.GetZ() * p.GetZ() + d0;
        return sgn(dist);
    }
};