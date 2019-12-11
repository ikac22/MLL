#ifndef _MLL_LAYER_CORELAYER_HPP
#define _MLL_LAYER_CORELAYER_HPP

#include<MLL/Math/matrix.hpp>
#include<MLL/Math/activation.hpp>

#include<MLL/Layer/layer.hpp>

namespace MLL{
    class CoreLayer : public Layer{
    private:

    protected:

    public:
        CoreLayer(int);

        virtual void compile() = 0;

        virtual void forward_propagation(const Layer&) = 0;
        virtual void back_propagation(const std::vector<float>&, const Layer&) = 0;
        virtual void back_propagation(const Layer&, const Layer&) = 0;

        virtual Layer* copy() const = 0;
    };
}

#endif//_MLL_LAYER_CORELAYER_HPP
