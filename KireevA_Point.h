#pragma once
#include "KireevA_Vector.h"
namespace KireevA
{
    class Point
    {
        friend Vector operator-(const Point & p1, const Point & p2);
        friend Point operator/(Point p, double div);
        friend Point operator+(Point p, const Vector& v);
        friend bool operator==(const Point & p1, const Point & p2);
        friend bool operator!=(const Point & p1, const Point & p2);
    public:
        Point() : m_x(0.0), m_y(0.0), m_z(0.0)
        {
        }
        Point(double x, double y, double z) : m_x(x), m_y(y), m_z(z)
        {
        }
        double GetX() const
        {
            return m_x;
        }
        double GetY() const
        {
            return m_y;
        }
        double GetZ() const
        {
            return m_z;
        }
        void SetX(double x)
        {
            m_x = x;
        }
        void SetY(double y)
        {
            m_y = y;
        }
        void SetZ(double z)
        {
            m_z = z;
        }
    private:
        double m_x, m_y, m_z;
    };
};