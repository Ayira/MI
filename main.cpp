#include <iostream>
#include <iomanip>
#include "Matrix.hpp"


const int N = 3;


int main()
{
    MI::Matrix A = MI::Matrix::Random(N);
    //MI::Matrix B = A.inverted_gauss_jordan();
    MI::Matrix C = A.inverted_blockwise();
   // MI::Matrix::print(B, N);
    std::cout<<std::endl;
    MI::Matrix::print(C, N);

    return 0;
}