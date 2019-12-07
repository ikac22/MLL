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

        void compile();

        void forward_propagation(const Layer&);
        void back_propagation(const Layer&);

        Layer* copy() const { return new Dense(*this); }
    };
}

#endif//_MLL_LAYER_CORE_DENSE_HPP
