#ifndef ADAGRAD_HPP_INCLUDED
#define ADAGRAD_HPP_INCLUDED

#include<MLL/Optimizer/optimizer.hpp>

template<class T>
class AdaGrad{};

template<>
class AdaGrad<Dense> : public Optimizer<Dense>{
    private:
        Matrix m_weight_GT;
        Matrix m_bias_GT;

    public:
        AdaGrad(float, float, int, int)

        void weight_cal() (Matrix&, const Matrix&);

        void bias_cal() (Matrix&, const Matrix&);

    };

#endif // ADAGRAD_HPP_INCLUDED
