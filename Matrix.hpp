#ifndef KURSACH_MATRIX_HPP
#define KURSACH_MATRIX_HPP


#include <cstddef>
#include <vector>

namespace MI
{
    class Matrix
    {
    public:
        Matrix(std::initializer_list<std::initializer_list<double>> list);
        Matrix(std::size_t n);
        Matrix(std::size_t n, std::size_t m);
        Matrix(const Matrix &copy);

        static Matrix Identity(std::size_t n);
        static Matrix Random(std:: size_t n);

        std::vector<double> & operator[] (std::size_t i);

        Matrix inverted_gauss_jordan();
        Matrix inverted_blockwise();

    private:
        std::vector<std::vector<double>> matrix;
    };
}


#endif //KURSACH_MATRIX_HPP
