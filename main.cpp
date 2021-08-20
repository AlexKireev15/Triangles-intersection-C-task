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

    
    /*{
        std::array<double, 9> t1, t2;
        for (size_t idx = 0; idx < 9; ++idx)
        {
            std::cin >> t1[idx];
        }
        for (size_t idx = 0; idx < 9; ++idx)
        {
            std::cin >> t2[idx];
        }

        bool answer = KireevA::HasIntersection(t1, t2);

        std::cout << std::endl;
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

        if (answer)
        {
            std::cout << "Has Intersection" << std::endl;
        }
        else
        {
            std::cout << "No Intersection" << std::endl;
        }
    }*/
    
    /*KireevA::Segment s(KireevA::Point(4., 4., 0.), KireevA::Point(2., 2., 0.));
    KireevA::Segment s2(KireevA::Point(4., 2., 0.), KireevA::Point(2., 4., 0.));
    auto res = s.Intersect(s2);

    for (auto it = res.begin(); it != res.end(); ++it)
    {
        std::cout << it->GetX() << " " << it->GetY() << " " << it->GetZ() << std::endl;
    }*/


    return 0;
}