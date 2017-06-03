#ifndef KURSACH_MATRIX_HPP
#define KURSACH_MATRIX_HPP


#include <cstddef>
#include <vector>
#include <iostream>

namespace MI
{
    class Matrix
    {
    public:
        Matrix(std::initializer_list<std::initializer_list<double>> list);
        explicit Matrix(std::size_t n);
        Matrix(std::size_t n, std::size_t m);
        Matrix(const Matrix &copy);
        Matrix & operator= (const Matrix &copy);

        static Matrix Identity(std::size_t n);
        static Matrix Random(std:: size_t n);
        static Matrix Random(std:: size_t n, std::size_t m);

        std::vector<double> & operator[] (std::size_t i);
        const std::vector<double> & operator[] (std::size_t i) const;

        Matrix inverted_gauss_jordan() const;
        Matrix inverted_blockwise() const;

        Matrix blockA() const;
        Matrix blockB() const;
        Matrix blockC() const;
        Matrix blockD() const;

        std::size_t rows() const;
        std::size_t cols() const;

    private:
        std::vector<std::vector<double>> matrix;
    };

    Matrix operator+ (const Matrix &A, const Matrix &B);
    Matrix operator- (const Matrix &A, const Matrix &B);
    Matrix operator* (const Matrix &A, const Matrix &B);
    Matrix operator- (const Matrix &A);

    std::ostream & operator<< (std::ostream &stream, const Matrix &A);
}


#endif //KURSACH_MATRIX_HPP
