#ifndef _MLL_LAYER_CONV_CONV2D_HPP
#define _MLL_LAYER_CONV_CONV2D_HPP

#include<initializer_list>

#include<MLL/Layer/layer.hpp>
#include<MLL/Layer/layer_shape.hpp>

namespace MLL{
    enum class Padding{
        valid,
        same
    };
    
    class Conv2D : public Layer{
    private:
        int m_kernel_count;
        LayerShape m_kernel_size;
        int m_pad_size;
        int m_stride;
        ActivationFunction m_fun;

        std::vector< std::vector<Matrix> > m_kernel;
        std::vector<float> m_bias;
    public:
        Conv2D(int, LayerShape, Padding = Padding::valid, int = 1,
               Activation = Activation::Linear, LayerShape = {0, 0});

        void compile();

        void forward_propagation(const Layer&);
        void back_propagation(const std::vector<float>&, const Layer&);
        void back_propagation(const Layer&, const Layer&);

        Layer* copy() const { return new Conv2D(*this); }
    };
}

#endif//_MLL_LAYER_CONV_CONV2D_HPP
