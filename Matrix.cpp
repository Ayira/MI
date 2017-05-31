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

    Matrix Matrix::inverted_gauss_jordan() const
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
        return Random(n, n);
    }

    Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list)
    {
        for (auto it = list.begin(); it != list.end() ; ++it)
        {
            matrix.push_back(std::vector<double>(*it));
        }
    }

    Matrix Matrix::inverted_blockwise() const
    {
        if(matrix.size() == 1)
        {
            return { { 1/matrix[0][0] } };
        }

        Matrix A = blockA();
        Matrix B = blockB();
        Matrix C = blockC();
        Matrix D = blockD();

        Matrix A1 = A.inverted_gauss_jordan() ;
        Matrix F1 = D - C*A1*B;
        Matrix F = F1.inverted_gauss_jordan();
        A = A1 + A1*B*F*C*A1;
        B = -A1*B*F;
        C = -F*C*A1;
        D = F;

        Matrix I(A.rows() + D.rows(), A.cols() + D.cols());

        for (int i = 0; i < I.rows(); ++i)
        {
            for (int j = 0; j < I.cols(); ++j)
            {
                if(i < A.rows() && j < A.cols())
                {
                    I[i][j] = A[i][j];
                }
                else if(i < A.rows())
                {
                    I[i][j] = B[i][j - A.cols()];
                }
                else if(j < A.cols())
                {
                    I[i][j] = C[i - A.rows()][j];
                }
                else
                {
                    I[i][j] = D[i - A.rows()][j - A.cols()];
                }

            }
        }

        return I;
    }

    Matrix Matrix::blockA() const
    {
        Matrix A(matrix.size()/2);
        for (int i = 0; i < matrix.size()/2; ++i)
        {
            for (int j = 0; j < matrix.size()/2; ++j)
            {
                A[i][j] = matrix[i][j];
            }
        }
        return A;
    }

    Matrix Matrix::blockB() const
    {
        int n = matrix.size()/2;
        int m = matrix.size() - (matrix.size()/2);
        Matrix B(n, m);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                B[i][j] = matrix[i][j + n];
            }
        }
        return B;
    }

    Matrix Matrix::blockC() const
    {
        int n = matrix.size() - (matrix.size()/2);
        int m = matrix.size()/2;

        Matrix C(n, m);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                C[i][j] = matrix[i + m][j];
            }
        }
        return C;
    }

    Matrix Matrix::blockD() const
    {
        int n = matrix.size()/2;
        int m = matrix.size() - (matrix.size()/2);

        Matrix D(m);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                D[i][j] = matrix[i + n][j + n];
            }
        }

        return D;
    }

    std::size_t Matrix::rows() const
    {
        return matrix.size();
    }

    std::size_t Matrix::cols() const
    {
        return matrix[0].size();
    }

    const std::vector<double> &Matrix::operator[](std::size_t i) const
    {
        return matrix[i];
    }

    Matrix Matrix::Random(std::size_t n, std::size_t m)
    {
        std::srand(std::time(0));

        Matrix A(n, m);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                A[i][j] = rand() % 200 - 100;
            }
        }

        return A;
    }

    Matrix &Matrix::operator=(const Matrix &copy)
    {
        matrix = copy.matrix;
        return *this;
    }

    void Matrix::print(Matrix A, std::size_t n)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                std::cout << std::fixed << std::setw(15) << std::setprecision(4) << A[i][j];
            }
            std::cout << std::endl;
        }
    }

    Matrix operator+ (const Matrix &A, const Matrix &B)
    {
        Matrix C(A.rows(), A.cols());

        for (int i = 0; i < C.cols(); ++i)
        {
            for (int j = 0; j < C.rows(); ++j)
            {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        return C;
    }

    Matrix operator- (const Matrix &A, const Matrix &B)
    {
        Matrix C(A.rows(), A.cols());

        for (int i = 0; i < C.cols(); ++i)
        {
            for (int j = 0; j < C.rows(); ++j)
            {
                C[i][j] = A[i][j] - B[i][j];
            }
        }
        return C;
    }

    Matrix operator* (const Matrix &A, const Matrix &B)
    {
        Matrix C(A.rows(), B.cols());

        for (int i = 0; i < C.cols(); ++i)
        {
            for (int j = 0; j < C.rows(); ++j)
            {
                for (int k = 0; k < A.cols(); ++k)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }

    Matrix operator-(const Matrix &A)
    {
        return Matrix(A.rows(), A.cols()) - A;
    }
}