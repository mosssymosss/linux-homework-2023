#include "complex_number.h"
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<ComplexNumber> vec = {{1,2},{5,-9},
                                      {8,8},{0,7},
                                      {-5,-3},{45,0},
                                      {7,-1},{-4,2},
                                      {0,0},{-6,-7},};
    std::sort(vec.begin(), vec.end(), [](const ComplexNumber& a, const ComplexNumber& b)
                                        {
                                            return a.get_modulus() < b.get_modulus();
                                        });
    for(int i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout<<std::endl;
    return 0;
}