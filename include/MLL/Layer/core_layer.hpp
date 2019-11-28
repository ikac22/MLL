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

        int get_size() const;

        virtual void forward_propagation(const CoreLayer&) = 0;
        //virtual void forward_propagation(const ConvLayer&) = 0;
        //virtual void forward_propagation(const PoolLayer&) = 0;

        virtual Layer* copy() const = 0;

        void set_activation(const std::vector<float>&);
        const std::vector<float>& get_activation() const;
    };
}

#endif//_MLL_LAYER_CORELAYER_HPP
