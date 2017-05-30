#include <iostream>
#include <iomanip>
#include "Matrix.hpp"


const int N = 3;
const int M = 3;


int main()
{
    MI::Matrix A = MI::Matrix::Random(N, M);

    //MI::Matrix B = A.inverted_gauss_jordan();
    MI::Matrix B = A.inverted_blockwise();
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            std::cout << std::setw(15) << B[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}