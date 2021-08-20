#include "KireevA_Line.h"
#include "KireevA_Utils.h"

namespace KireevA
{
    Line::Line(const Plane & p1, const Plane & p2)
    {
        Vector n1 = p1.GetNormal(),
               n2 = p2.GetNormal();
        double d1 = p1.GetD(),
               d2 = p2.GetD();
        m_dir = n1.CrossProduct(n2);

        double div = m_dir.GetX()* m_dir.GetX() + m_dir.GetY() * m_dir.GetY() + m_dir.GetZ() * m_dir.GetZ();
        m_p.SetX(m_dir.GetY() * (n2.GetZ() * d1 - n1.GetZ() * d2) - m_dir.GetZ() * (n2.GetY() * d1 - n1.GetY() * d2));
        m_p.SetY(m_dir.GetZ() * (n2.GetX() * d1 - n1.GetX() * d2) - m_dir.GetX() * (n2.GetZ() * d1 - n1.GetZ() * d2));
        m_p.SetZ(m_dir.GetX() * (n2.GetY() * d1 - n1.GetY() * d2) - m_dir.GetY() * (n2.GetX() * d1 - n1.GetX() * d2));
        m_p = m_p / div;
    }
    double Line::GetParameter(const Point & p) const
    {
        if (!eq0(m_dir.GetX()))
        {
            return (p.GetX() - m_p.GetX()) / m_dir.GetX();
        }
        if (!eq0(m_dir.GetY()))
        {
            return (p.GetY() - m_p.GetY()) / m_dir.GetY();
        }
        if (!eq0(m_dir.GetZ()))
        {
            return (p.GetZ() - m_p.GetZ()) / m_dir.GetZ();
        }
        return 0.0;
    }

    bool Line::Contains(const Point & p) const
    {
        return IsNullVector(m_dir.CrossProduct(p - m_p));
    }

    std::vector<Point> Line::Distance(const Line& l) const
    {
        Point p1 = m_p,
            p2 = m_p + m_dir,
            p3 = l.m_p,
            p4 = l.m_p + l.m_dir;

        Vector p13 = p1 - p3,
            p43 = p4 - p3,
            p21 = p2 - p1;

        if (IsNullVector(p43))
        {
            return std::vector<Point>();
        }
        if (IsNullVector(p21))
        {
            return std::vector<Point>();
        }

        double d1343 = p13.ScalarProduct(p43);
        double d4321 = p43.ScalarProduct(p21);
        double d1321 = p13.ScalarProduct(p21);
        double d4343 = p43.ScalarProduct(p43);
        double d2121 = p21.ScalarProduct(p21);

        double denom = d2121 * d4343 - d4321 * d4321;
        if (eq0(denom))
        {
            return std::vector<Point>();
        }

        double numer = d1343 * d4321 - d1321 * d4343;

        double ma = numer / denom;
        double mb = (d1343 + d4321 * ma) / d4343;

        Point pa = p1 + p21 * ma;
        Point pb = p3 + p43 * mb;

        return std::vector<Point>{pa, pb};
    }

    std::vector<Point> Line::Intersect(const Line& l) const
    {
        Vector v = l.m_p - m_p;
        double det = v.CrossProduct(m_dir).ScalarProduct(l.m_dir);
        if (!eq0(det))
        {
            return std::vector<Point>();
        }

        if (IsNullVector(m_dir.CrossProduct(l.m_dir)))
        {
            if (Contains(l.m_p))
            {
                return std::vector<Point> { m_p, l.m_p };
            }
            else
            {
                return std::vector<Point>();
            }
        }

        std::vector<Point> result = Distance(l);

        if(result.size() >= 2)
        {
            if(result[0] == result[1])
            {
                return std::vector<Point> { result[0] };
            }
        }

        return std::vector<Point>();
    }
}
