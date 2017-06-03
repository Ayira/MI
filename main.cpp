#include <iostream>
#include <iomanip>
#include "Matrix.hpp"


const int N = 3;


int main()
{
    MI::Matrix A = MI::Matrix::Random(N);

    std::cout << A << std::endl;
    auto D = A.blockD();
    std::cout << D << std::endl;

    return 0;
}