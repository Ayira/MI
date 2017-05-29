#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Matrix.hpp"


namespace MI
{

    Matrix::Matrix(std::size_t n) : Matrix(n, n)
    {

    }

    Matrix::Matrix(std::size_t n, std::size_t m) : matrix(n, std::vector<double>(m))
    {

    }

    Matrix Matrix::inverted_gauss_jordan()
    {
        Matrix A(*this);
        Matrix I = Matrix::Identity(matrix.size());

        for (int i = 0; i < matrix.size(); ++i)
        {
            if(A[i][i] == 0)
            {
                for (int j = i+1; j < matrix.size(); ++j)
                {
                    if(A[j][i] != 0)
                    {
                        for (int k = 0; k < matrix.size(); ++k)
                        {
                            A[i][k] += A[j][k];
                            I[i][k] += I[j][k];
                        }
                        break;
                    }
                }
            }

            double temp = A[i][i];

            if(temp == 0)
            {
                return Matrix(matrix.size());
            }

            for (int j = 0; j < matrix.size(); ++j)
            {
                A[i][j] /= temp;
                I[i][j] /= temp;

            }

            for (int j = i+1; j < matrix.size(); ++j)
            {
                temp = A[j][i];
                for (int k = 0; k < matrix.size(); ++k)
                {
                    A[j][k] -= temp *  A[i][k];
                    I[j][k] -= temp *  I[i][k];
                }
            }
        }

        for (int i = matrix.size() - 1; i >= 0; --i)
        {
            for (int j = i-1; j >= 0; --j)
            {
                double temp = A[j][i];
                for (int k = 0; k < matrix.size(); ++k)
                {
                    A[j][k] -= temp * A[i][k];
                    I[j][k] -= temp * I[i][k];
                }
            }
        }

        return I;
    }

    Matrix::Matrix(const Matrix &copy) : matrix(copy.matrix)
    {

    }

    Matrix Matrix::Identity(std::size_t n)
    {
        Matrix I(n);

        for (int i = 0; i < n; ++i)
        {
            I[i][i] = 1;
        }

        return I;
    }

    std::vector<double> & Matrix::operator[] (std::size_t i)
    {
        return matrix[i];
    }

    Matrix Matrix::Random(std::size_t n)
    {
        std::srand(std::time(0));

        Matrix A(n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                A[i][j] =rand()% 200 - 100;
            }
        }

        return A;
    }

    Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list)
    {
        for (auto it = list.begin(); it != list.end() ; ++it)
        {
            matrix.push_back(std::vector<double>(*it));
        }
    }

    Matrix Matrix::inverted_blockwise()
    {
        return Matrix(std::initializer_list<initializer_list < double>>
        ());
    }
}