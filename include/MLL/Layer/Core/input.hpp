#ifndef _MLL_LAYER_CORE_INPUT_HPP
#define _MLL_LAYER_CORE_INPUT_HPP

#include<MLL/Layer/layer.hpp>

namespace MLL{
    class Input : public Layer{
    private:

    public:
        Input(int);

        void compile();

        void forward_propagation(const Layer&);
        void back_propagation(const std::vector<float>&, const Layer&){}
        void back_propagation(const Layer&, const Layer&){}

        Layer* copy() const { return new Input(*this); }

        float prev_agrad(int, int) const {}
        void apply_gradient(int){}
    };
}

#endif//_MLL_LAYER_CORE_INPUT_HPP
