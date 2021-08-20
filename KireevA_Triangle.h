#pragma once
#include "KireevA_Plane.h"
#include "KireevA_Point.h"
#include "KireevA_Segment.h"

#include <vector>
#include <array>

namespace KireevA
{
    class Triangle
    {
    public:
        Triangle(){}
        Triangle(const std::array<double, 9>& coords);
        Triangle(const std::vector<Point>& points);
        Plane GetPlane() const
        {
            return m_plane;
        }
        Point GetVert(size_t index) const
        {
            if (index < m_verts.size())
            {
                return m_verts[index];
            }
            return Point();
        }
        std::vector<Point> GetVerts() const
        {
            return m_verts;
        }
        bool HasIntersection(const Point& p) const;
        bool HasIntersection(const Segment& s) const;
        bool HasIntersection(const Triangle& t) const;
    private:
        bool PlanarHasIntersection(const Triangle& t) const;

        Plane m_plane;
        std::vector<Point> m_verts;
    };
};