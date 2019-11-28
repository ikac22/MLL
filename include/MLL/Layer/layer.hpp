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
        virtual int get_size() const = 0;

        virtual void forward_propagation(const CoreLayer&) = 0;
        //virtual void forward_propagation(const ConvLayer&) = 0;
        //virtual void forward_propagation(const PoolLayer&) = 0;

        virtual Layer* copy() const = 0;

        virtual void set_activation(const std::vector<float>&) = 0;
        virtual const std::vector<float>& get_activation() const = 0;

    };

}

#endif//_MLL_LAYER_LAYER_HPP
