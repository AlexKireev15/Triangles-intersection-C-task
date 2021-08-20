#include <fstream>
#include <iostream>
#include <array>

#include "KireevA_Intersection.h"

/*
    Use function
        bool HasIntersection(const std::array<double, 9> & , const std::array<double, 9> & )
    to get true if 2 triangles is intersected or false if not
*/

std::string boolToString(bool b)
{
    if (b)
    {
        return "True";
    }
    return "False";
}

int main()
{
    {
        std::ifstream in("tests.txt");
        if (in.is_open())
        {
            size_t testIdx = 0;
            while(in.good())
            {
                std::array<double, 9> t1, t2;
                bool expected = false;
                for (size_t idx = 0; idx < t1.size(); ++idx)
                {
                    in >> t1[idx];
                }
                for (size_t idx = 0; idx < t2.size(); ++idx)
                {
                    in >> t2[idx];
                }
                in >> expected;

                bool answer = KireevA::HasIntersection(t1, t2);

                if (expected != answer)
                {
                    std::cout << "Test number " << testIdx + 1 << " failed" << std::endl;
                    std::cout << "expected " << boolToString(expected) << ", but got " << boolToString(answer) << std::endl;
                    std::cout << "Test values: " << std::endl;
                    for (size_t idx = 0; idx < 3; ++idx)
                    {
                        for (size_t jdx = 0; jdx < 3; ++jdx)
                        {
                            std::cout << t1[idx * 3 + jdx] << "; ";
                        }
                        std::cout << std::endl;
                    }
                    std::cout << std::endl;
                    for (size_t idx = 0; idx < 3; ++idx)
                    {
                        for (size_t jdx = 0; jdx < 3; ++jdx)
                        {
                            std::cout << t2[idx * 3 + jdx] << "; ";
                        }
                        std::cout << std::endl;
                    }
                    std::cout << std::endl << "---------------------------------------------------------------------------------" << std::endl;
                }
                testIdx++;
            }
        }

        in.close();
    }
    return 0;
}
