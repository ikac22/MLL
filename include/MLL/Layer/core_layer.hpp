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

        void set_size(int);
    public:
        CoreLayer(int);

        virtual void forward_propagation(const CoreLayer&);
        //virtual void forward_propagation(const ConvLayer&) = 0;
        //virtual void forward_propagation(const PoolLayer&) = 0;

        virtual Layer* copy() const;

        void set_activation(const std::vector<float>&);
        const Matrix& get_activation() const { return m_activation; }

        const std::array<int, 3> get_shape() const;
    };
}

#endif//_MLL_LAYER_CORELAYER_HPP
