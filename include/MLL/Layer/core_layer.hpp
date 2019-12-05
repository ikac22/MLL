#ifndef _MLL_LAYER_CORELAYER_HPP
#define _MLL_LAYER_CORELAYER_HPP

#include<MLL/Math/matrix.hpp>
#include<MLL/Math/activation.hpp>

#include<MLL/Layer/layer.hpp>

namespace MLL{

    class CoreLayer : public Layer{
    private:

    protected:
        Matrix m_activation;
        Matrix m_sum;
    public:
        CoreLayer(int);
    };
}

#endif//_MLL_LAYER_CORELAYER_HPP
