#ifndef _MLL_OPTIMIZER_OPTIMIZER_HPP
#define _MLL_OPTIMIZER_OPTIMIZER_HPP

#include<MLL/Layer/Core/dense.hpp>
#include<MLL/Layer/Conv/conv2d.hpp>

namespace MLL{

    template<class T>
    class Optimizer{};

    template<>
    class Optimizer <Dense>{
    private:

    protected:
        float m_learning_rate, m_epsilon, m_decay;

    public:
        Optimizer(float, float, float);

        virtual void weight_cal (Matrix&, const Matrix&) = 0;///WEIGHTS

        virtual void bias_cal (Matrix&, const Matrix&) = 0;///BIASES
    };

    template<>
    class Optimizer <Conv2D>{};
}

#endif//_MLL_OPTIMIZER_OPTIMIZER_HPP
