#ifndef _MLL_MATH_MATRIX_HPP
#define _MLL_MATH_MATRIX_HPP

#include<iostream>
#include<vector>

namespace MLL{
    struct LayerShape;

    class Matrix{
    private:
        std::vector< std::vector<float> > m_matrix;

        int m_height;
        int m_width;
    public:
        Matrix();
        Matrix(int, int);
        Matrix(int, int, const std::vector<float>&);

        Matrix& operator=(const Matrix&);

        std::vector<float>& operator[](int i){ return m_matrix[i]; }
        const std::vector<float>& operator[](int i) const { return m_matrix[i]; }

        friend const Matrix& operator+(const Matrix&, const Matrix&);
        friend const Matrix& operator*(const Matrix&, const Matrix&);

        void resize(int, int);

        int get_height() const { return m_height; }
        int get_width() const { return m_width; }

        const std::vector<float>& to_array() const;
    };

    const Matrix& operator+(const Matrix&, const Matrix&);
    const Matrix& operator*(const Matrix&, const Matrix&);

    void gemm(const Matrix&, const Matrix&, Matrix&);
    float get_kernel_sum(const std::vector<Matrix>&, const std::vector<Matrix>&,
                         LayerShape, float, int, int);
}

#endif//_MLL_MATH_MATRIX_HPP
