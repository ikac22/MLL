#ifndef _MLL_LAYER_CONVLAYER_HPP
#define _MLL_LAYER_CONVLAYER_HPP

#include<MLL/Layer/layer_shape.hpp>

namespace MLL{
    enum class Padding{
        valid,
        same
    };

    class ConvLayer : public Layer{
    private:

    protected:

    public:
        ConvLayer(LayerShape);

        virtual void compile() = 0;

        virtual void forward_propagation(const Layer&) = 0;
        virtual void back_propagation(const std::vector<float>&, const Layer&) = 0;
        virtual void back_propagation(const Layer&, const Layer&) = 0;

        virtual Layer* copy() const = 0;
    };
}

#endif//_MLL_LAYER_CONVLAYER_HPP
