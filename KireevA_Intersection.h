#pragma once
#include <array>
#include "KireevA_Point.h"
#include "KireevA_Plane.h"
namespace KireevA
{
    bool HasIntersection(const std::array<double, 9> & , const std::array<double, 9> & );
};