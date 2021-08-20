#pragma once
#include "KireevA_Segment.h"
#include "KireevA_Utils.h"

namespace KireevA
{
    bool Segment::Contains(const Point& p) const
    {
        double maxParameter = GetParameter(m_maxPoint);
        double minParameter = GetParameter(m_minPoint);
        double parameter = GetParameter(p);

        return Line::Contains(p) && parameter < maxParameter&& parameter > minParameter;
    }

    bool Segment::HasIntersection(const Segment& s) const
    {
        if (m_maxPoint == m_minPoint)
        {
            if (s.m_maxPoint == s.m_minPoint)
            {
                return m_maxPoint == s.m_maxPoint;
            }
            else
            {
                return s.Contains(m_maxPoint);
            }
        }
        else if (s.m_maxPoint == s.m_minPoint)
        {
            return Contains(s.m_maxPoint);
        }

        Plane p(m_maxPoint, m_minPoint, s.m_maxPoint);
        if (IsNullVector(p.GetNormal()))
        {
            return true;
        }

        auto CrossProductTest = [&p](const Point& p1, const Point& p2, const Point& p3, const Point& p4)
        {
            Vector v = p2 - p1;
            Vector v1 = p3 - p1;
            Vector v2 = p4 - p1;

            int sgn1 = sgn(v.CrossProduct(v1).ScalarProduct(p.GetNormal()));
            int sgn2 = sgn(v.CrossProduct(v2).ScalarProduct(p.GetNormal()));

            return (sgn1 == 0 || sgn2 == 0) || (sgn1 != sgn2);
        };

        return CrossProductTest(m_minPoint, m_maxPoint, s.m_minPoint, s.m_maxPoint) &&
               CrossProductTest(m_maxPoint, m_minPoint, s.m_minPoint, s.m_maxPoint) &&
               CrossProductTest(s.m_minPoint, s.m_maxPoint, m_minPoint, m_maxPoint) &&
               CrossProductTest(s.m_maxPoint, s.m_minPoint, m_minPoint, m_maxPoint);
    }

    std::vector<Point> Segment::Intersect(const Line& s) const
    {
        std::vector<Point> res = s.Intersect(*this);
        if (res.empty())
        {
            return res;
        }
        if (res.size() == 2)
        {
            return std::vector<Point> { m_minPoint, m_maxPoint };
        }
        double t = GetParameter(res[0]),
               tmin = GetParameter(m_minPoint),
               tmax = GetParameter(m_maxPoint);
        if (t <= tmax && t >= tmin)
        {
            return res;
        }

        return std::vector<Point>();
    }
};