#ifndef _MLL_MATH_GRADIENT_HPP
#define _MLL_MATH_GRADIENT_HPP

#include<MLL/Math/matrix.hpp>

namespace MLL{
    class Dense;
    class Flatten;
    class Input;

    template<class T>
    class Gradient{
    private:

    public:

    };

    template<>
    class Gradient<Dense>{
    private:
        Matrix m_weight;
        Matrix m_activation;
        Matrix m_bias;
    public:
        Gradient();

        Matrix& w(){ return m_weight; }
        Matrix& a(){ return m_activation; }
        Matrix& b(){ return m_bias; }
    };
}

#endif//_MLL_MATH_GRADIENT_HPP
