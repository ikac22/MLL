#ifndef _MLL_LAYER_LAYER_HPP
#define _MLL_LAYER_LAYER_HPP

namespace MLL{
    class CoreLayer;
    class ConvLayer;
    class PoolLayer;

    class Layer{
    private:

    protected:

    public:
        virtual void forward_propagation(const CoreLayer&) = 0;
        //virtual void forward_propagation(const ConvLayer&) = 0;
        //virtual void forward_propagation(const PoolLayer&) = 0;

        virtual void back_propagation(const CoreLayer&) = 0;
        //virtual void back_propagation(const ConvLayer&) = 0;
        //virtual void back_propagation(const PoolLayer&) = 0;

        virtual Layer* copy() const = 0;
    };

}

#endif//_MLL_LAYER_LAYER_HPP
