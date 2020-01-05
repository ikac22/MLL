#ifndef _MLL_OPTIMIZER_OPTIMIZER_HPP
#define _MLL_OPTIMIZER_OPTIMIZER_HPP

#include<MLL/Layer/Core/dense.hpp>
#include<MLL/Layer/Conv/conv2d.hpp>

namespace MLL{
    enum class Optimizer{
        SGD,
        Adagrad,
        AdaDelta,
        Adam
    };

    class LayerOptimizer{
    private:

    protected:

    public:

    };

    class SGD : public LayerOptimizer{

    };

    class Adagrad : public LayerOptimizer{

    };
}

#endif//_MLL_OPTIMIZER_OPTIMIZER_HPP
