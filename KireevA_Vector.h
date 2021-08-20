#pragma once
#include <math.h>
namespace KireevA
{
    class Vector
    {
    public:
        Vector() : m_x(0.0), m_y(0.0), m_z(0.0)
        {
        }
        Vector(double x, double y, double z) : m_x(x), m_y(y), m_z(z)
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
        double ScalarProduct(const Vector & v) const
        {
            return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z;
        }
        Vector CrossProduct(const Vector & v) const
        {
            return Vector(m_y * v.m_z - m_z * v.m_y, m_z * v.m_x - m_x * v.m_z, m_x * v.m_y - m_y * v.m_x);
        }
        double GetAbs() const
        {
            return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
        }
        

        friend Vector operator*(Vector v, double fact);
        friend Vector operator/(Vector v, double fact);
    private:
        double m_x, m_y, m_z;
    };
};