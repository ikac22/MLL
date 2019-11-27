#ifndef _MLL_LAYER_CORE_DENSE_HPP
#define _MLL_LAYER_CORE_DENSE_HPP

#include<MLL/Layer/core_layer.hpp>

#include<MLL/Math/activation.hpp>

namespace MLL{
    class Dense : public CoreLayer{
    private:
        ActivationFunction m_fun;
    public:
        Dense(int, Activation);
    };
}

#endif//_MLL_LAYER_CORE_DENSE_HPP
