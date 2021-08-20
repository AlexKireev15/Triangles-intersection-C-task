#pragma once

#include "KireevA_Line.h"

namespace KireevA
{
    class Segment : public Line
    {
    public:
        Segment() {}
        Segment(const Line& line, const Point& maxPoint, const Point& minPoint) : Line(line), m_maxPoint(maxPoint), m_minPoint(minPoint)
        {
        }
        Segment(const Point& maxPoint, const Point& minPoint) : Line(maxPoint - minPoint, minPoint), m_maxPoint(maxPoint), m_minPoint(minPoint)
        {
        }
        bool Contains(const Point& p) const override;
        Point GetMaxPoint() const
        {
            return m_maxPoint;
        }
        Point GetMinPoint() const
        {
            return m_minPoint;
        }
        bool HasIntersection(const Segment& s) const;
        std::vector<Point> Intersect(const Line& s) const;
    private:
        Point m_maxPoint;
        Point m_minPoint;
    };
};