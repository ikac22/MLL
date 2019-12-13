#ifndef _MLL_MATH_GRADIENT_HPP
#define _MLL_MATH_GRADIENT_HPP

#include<MLL/Math/matrix.hpp>

namespace MLL{
    class Dense;
    class Flatten;
    class Input;

    template<class T>
    class Gradient{};

    template<>
    class Gradient<Dense>{
    private:
        Matrix m_weight;
        Matrix m_activation;
        Matrix m_bias;
    public:
        Matrix& get_w(){ return m_weight; }
        Matrix& get_a(){ return m_activation; }
        Matrix& get_b(){ return m_bias; }

        const Matrix& w() const{ return m_weight; }
        const Matrix& a() const{ return m_activation; }
        const Matrix& b() const{ return m_bias; }

        void set_size(int, int);
    };
}

#endif//_MLL_MATH_GRADIENT_HPP
