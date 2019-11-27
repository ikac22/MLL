#ifndef _MLL_MATH_ACTIVATION_HPP
#define _MLL_MATH_ACTIVATION_HPP

#include<functional>
#include<math.h>

namespace MLL{
    class Matrix;

    enum class Activation{
        Linear,
        Sigmoid,
        ReLU
    };

    class ActivationFunction{
    private:
        std::function<float(float)> m_activation_fun;
        std::function<float(float)> m_activation_deriv;
    public:
        ActivationFunction(Activation);

        float operator()(float) const;
        float operator[](float) const;

        const Matrix& operator()(const Matrix&) const;
        const Matrix& operator[](const Matrix&) const;
    };

    namespace Activations{
        float linear_f(float);
        float linear_d(float);

        float sigmoid_f(float);
        float sigmoid_d(float);

        float relu_f(float);
        float relu_d(float);
    }
}

#endif//_MLL_MATH_ACTIVATION_HPP
