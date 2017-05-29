#include <iostream>
#include <iomanip>
#include "Matrix.hpp"


const int N = 3;


int main()
{
    MI::Matrix A = {
            {1, 2, 3},
            {2, 4, 7},
            {5, 10, 1},
    };


    MI::Matrix B = A.inverted_gauss_jordan();

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << std::setw(15) << B[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}