#include <iostream>
#include <iomanip>
#include "Matrix.hpp"


const int N = 3;


int main()
{
    MI::Matrix A = {
            {1, 2, 3},
            {4, 0, 6},
            {7, 8, 9},
    };

    std::cout << A << std::endl;

    std::cout << A.inverted_gauss_jordan() << std::endl;
    std::cout << A.inverted_blockwise() << std::endl;

    return 0;
}