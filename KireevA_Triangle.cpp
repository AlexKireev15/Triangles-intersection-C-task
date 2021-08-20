#include "KireevA_Triangle.h"
#include "KireevA_Utils.h"

#include <algorithm>

namespace KireevA
{
    Triangle::Triangle(const std::array<double, 9> & coords)
    {
        m_verts = 
        { 
            Point(coords[0], coords[1], coords[2]),
            Point(coords[3], coords[4], coords[5]),
            Point(coords[6], coords[7], coords[8])
        };

        m_plane = Plane(m_verts[0], m_verts[1], m_verts[2]);
    }

    Triangle::Triangle(const std::vector<Point>& points)
    {
        if (points.size() < 3)
        {
            return;
        }
        m_verts = points;
        m_plane = Plane(m_verts[0], m_verts[1], m_verts[2]);
    }

    bool Triangle::HasIntersection(const Point& p) const
    {
        if (!eq0(m_plane.Distance(p)))
        {
            return false;
        }

        return IsPointInsidePoints(p, m_verts, m_plane);
    }

    bool Triangle::HasIntersection(const Segment& s) const
    {
        Segment s1(m_verts[0], m_verts[1]), s2(m_verts[1], m_verts[2]), s3(m_verts[2], m_verts[0]);
        if (s.HasIntersection(s1) || s.HasIntersection(s2) || s.HasIntersection(s3))
        {
            return true;
        }
        return IsPointInsidePoints(s.GetMaxPoint(), m_verts, m_plane);
    }

    int SortByOneSgn(Point& v1, Point& v2, Point& v3, const Plane& p)
    {
        double dist1 = p.SgnDistance(v1), dist2 = p.SgnDistance(v2), dist3 = p.SgnDistance(v3);
        if (sgn(dist1) == sgn(dist2) && sgn(dist1) == sgn(dist3))
        {
            if (dist1 != 0.0)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }

        if (sgn(dist2) == sgn(dist3))
        {
            std::swap(v1, v3);
        }
        else if (sgn(dist1) == sgn(dist3))
        {
            std::swap(v2, v3);
        }

        return 1;
    }

    bool Triangle::PlanarHasIntersection(const Triangle& t) const
    {
        Segment s1(t.m_verts[0], t.m_verts[1]), s2(t.m_verts[1], t.m_verts[2]), s3(t.m_verts[2], t.m_verts[0]);
        return HasIntersection(s1) || HasIntersection(s2) || HasIntersection(s3) || t.HasIntersection(m_verts[0]);
    }

    bool Triangle::HasIntersection(const Triangle& t) const
    {
        Point p11 = m_verts[0], p12 = m_verts[1], p13 = m_verts[2];
        Point p21 = t.m_verts[0], p22 = t.m_verts[1], p23 = t.m_verts[2];
        Plane p1 = m_plane, p2 = t.m_plane;
        int sortResult = SortByOneSgn(p11, p12, p13, p2);
        if (sortResult < 0)
        {
            return false;
        }
        if (sortResult == 0)
        {
            return PlanarHasIntersection(t);
        }
        
        sortResult = SortByOneSgn(p21, p22, p23, p1);
        if (sortResult < 0)
        {
            return false;
        }

        Line planeIntersection(p1, p2);

        std::vector<double> intersectionParams1, intersectionParams2;

        auto add = [&planeIntersection](std::vector<double>& to, const std::vector<Point>& from)
        {
            for (auto it = from.begin(); it != from.end(); ++it)
            {
                to.push_back(planeIntersection.GetParameter(*it));
            }
        };

        Segment s11(p11, p13), s12(p12, p13),
                s21(p21, p23), s22(p22, p23);

        add(intersectionParams1, s11.Intersect(planeIntersection));
        add(intersectionParams1, s12.Intersect(planeIntersection));

        auto minMaxParam1 = std::minmax_element(intersectionParams1.begin(), intersectionParams1.end());

        add(intersectionParams2, s21.Intersect(planeIntersection));
        add(intersectionParams2, s22.Intersect(planeIntersection));

        auto minMaxParam2 = std::minmax_element(intersectionParams2.begin(), intersectionParams2.end());

        if (intersectionParams1.empty() || intersectionParams2.empty())
        {
            return false;
        }

        if (*minMaxParam2.first > *minMaxParam1.second || *minMaxParam1.first > *minMaxParam2.second)
        {
            return false;
        }

        return true;
    }
}