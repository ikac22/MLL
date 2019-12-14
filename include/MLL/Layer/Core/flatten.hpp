#ifndef _MLL_LAYER_CORE_FLATTEN_HPP
#define _MLL_LAYER_CORE_FLATTEN_HPP

#include<MLL/Layer/layer.hpp>

namespace MLL{
    class Flatten : public Layer{
    private:

    public:
        Flatten();

        void compile();

        float prev_agrad(int, int) const;

        void forward_propagation(const Layer&);
        void back_propagation(const std::vector<float>&, const Layer&);
        void back_propagation(const Layer&, const Layer&);

        Layer* copy() const { return new Flatten(*this); }

        void apply_gradient(){}
    };
}

#endif//_MLL_LAYER_CORE_FLATTEN_HPP
