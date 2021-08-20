#include "KireevA_Intersection.h"
#include "KireevA_Triangle.h"
#include "KireevA_Line.h"
#include "KireevA_Utils.h"

#include <vector>

namespace KireevA
{
    std::vector<Point> GetAllPoints(std::vector<std::vector<Point>>& vertices)
    {
        std::vector<Point> result;
        if (vertices.empty())
        {
            return result;
        }

        for (auto it = vertices.begin(); it != vertices.end();)
        {
            if ((*it)[0] == (*it)[1] && (*it)[0] == (*it)[2])
            {
                result.push_back((*it)[0]);
                it = vertices.erase(it);
                continue;
            }   
            ++it;
        }

        return result;
    }

    std::vector<Segment> GetAllSegments(std::vector<std::vector<Point>>& vertices)
    {
        std::vector<Segment> result;
        if (vertices.empty())
        {
            return result;
        }

        for (auto it = vertices.begin(); it != vertices.end();)
        {
            Vector v1 = (*it)[1] - (*it)[0];
            Vector v2 = (*it)[2] - (*it)[0];
            if (IsNullVector(v1.CrossProduct(v2)))
            {
                Line line(v1, (*it)[0]);
                if (line.Contains((*it)[0]) && line.Contains((*it)[1]) && line.Contains((*it)[2]))
                {
                    double t0 = line.GetParameter((*it)[0]);
                    double t1 = line.GetParameter((*it)[1]);
                    double t2 = line.GetParameter((*it)[2]);
                    double maxT = std::max({ t0, t1, t2 });
                    double minT = std::min({ t0, t1, t2 });
                    result.push_back(Segment(line, line.GetPoint(maxT), line.GetPoint(minT)));
                    it = vertices.erase(it);
                    continue;
                }
            }
            ++it;
        }
        return result;
    }

    std::vector<Triangle> GetAllTriangles(std::vector<std::vector<Point>>& vertices)
    {
        std::vector<Triangle> result;
        if (vertices.empty())
        {
            return result;
        }

        for (auto it = vertices.begin(); it != vertices.end();)
        {
            Triangle triangle(*it);
            if (!IsNullVector(triangle.GetPlane().GetNormal()))
            {
                result.push_back(triangle);
                it = vertices.erase(it);
                continue;
            }
            ++it;
        }
        return result;
    }

    bool HasIntersection(const std::array<double, 9> & T1, const std::array<double, 9> & T2)
    {
        Point v11(T1[0], T1[1], T1[2]),
              v12(T1[3], T1[4], T1[5]),
              v13(T1[6], T1[7], T1[8]);

        Point v21(T2[0], T2[1], T2[2]),
              v22(T2[3], T2[4], T2[5]),
              v23(T2[6], T2[7], T2[8]);

        std::vector<std::vector<Point>> vertices = { 
            std::vector<Point> {v11, v12, v13},
            std::vector<Point>{v21, v22, v23} 
        };

        std::vector<Point> points = GetAllPoints(vertices);
        std::vector<Segment> segments = GetAllSegments(vertices);
        std::vector<Triangle> triangles = GetAllTriangles(vertices);
        
        for (auto it = triangles.begin(); it != triangles.end(); ++it)
        {
            if ((it + 1) != triangles.end())
            {
                return it->HasIntersection(*(it + 1));
            }
            for (auto jt = segments.begin(); jt != segments.end(); ++jt)
            {
                return it->HasIntersection(*jt);
            }
            for (auto jt = points.begin(); jt != points.end(); ++jt)
            {
                return it->HasIntersection(*jt);
            }
        }

        for (auto it = segments.begin(); it != segments.end(); ++it)
        {
            if ((it + 1) != segments.end())
            {
                return it->HasIntersection(*(it + 1));
            }
            for (auto jt = points.begin(); jt != points.end(); ++jt)
            {
                return it->Contains(*jt);
            }
        }

        for (auto it = points.begin(); it != points.end(); ++it)
        {
            if ((it + 1) != points.end())
            {
                return (*it) == (*(it + 1));
            }
        }

        return false;
    }
};