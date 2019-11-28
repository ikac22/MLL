#ifndef _MLL_LAYER_CORE_DENSE_HPP
#define _MLL_LAYER_CORE_DENSE_HPP

#include<MLL/Layer/core_layer.hpp>

#include<MLL/Math/activation.hpp>

namespace MLL{
    class Dense : public CoreLayer{
    private:
        Matrix m_weight;
        Matrix m_bias;

        ActivationFunction m_fun;
    public:
        Dense(int, Activation);

        void forward_propagation(const CoreLayer&);

        Layer* copy() const;
    };
}

#endif//_MLL_LAYER_CORE_DENSE_HPP
