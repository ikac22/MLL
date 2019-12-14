#ifndef _MLL_LAYER_CORE_FLATTEN_HPP
#define _MLL_LAYER_CORE_FLATTEN_HPP

#include<MLL/Layer/layer.hpp>

namespace MLL{
    class Flatten : public Layer{
    private:

    public:
        Flatten();

        void compile();

        void forward_propagation(const Layer&);
        void back_propagation(const std::vector<float>&, const Layer&);
        void back_propagation(const Layer&, const Layer&);

        Layer* copy() const { return new Flatten(*this); }

        float prev_agrad(int, int) const;
        void apply_gradient(int){}
    };
}

#endif//_MLL_LAYER_CORE_FLATTEN_HPP
