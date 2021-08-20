#include "KireevA_Vector.h"

namespace KireevA
{
    Vector operator*(Vector v1, double fact)
    {
        v1.m_x *= fact;
        v1.m_y *= fact;
        v1.m_z *= fact;
        return v1;
    }
    Vector operator/(Vector v1, double fact)
    {
        v1.m_x /= fact;
        v1.m_y /= fact;
        v1.m_z /= fact;
        return v1;
    }
}