#ifndef _MLL_MATH_MATRIX_HPP
#define _MLL_MATH_MATRIX_HPP

#include<iostream>
#include<vector>

namespace MLL{
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

        friend Matrix& operator+(const Matrix&, const Matrix&);
        friend Matrix& operator*(const Matrix&, const Matrix&);

        void resize(int, int);

        int get_height() const { return m_height; }
        int get_width() const { return m_width; }

        void output() const {   // TODO: Remove
            std::cout << "[" << m_height << "x" << m_width << "]" << std::endl;
            for(int i = 0; i < m_height; ++i){
                for(int j = 0; j < m_width; ++j){
                    std::cout << m_matrix[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    };

    Matrix& operator+(const Matrix&, const Matrix&);
    Matrix& operator*(const Matrix&, const Matrix&);
}

#endif//_MLL_MATH_MATRIX_HPP
