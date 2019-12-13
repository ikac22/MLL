#ifndef _MLL_LAYER_LAYER_HPP
#define _MLL_LAYER_LAYER_HPP

#include<vector>

#include<MLL/Layer/layer_shape.hpp>

namespace MLL{
    class CoreLayer;
    class ConvLayer;
    class PoolLayer;

    class Layer{
    private:

    public:
        std::vector<Matrix> m_activation;
        std::vector<Matrix> m_sum;

        LayerShape m_input_shape;
        LayerShape m_output_shape;
    public:
        Layer(LayerShape);

        virtual void compile() = 0;

        void set_input_shape(LayerShape t_shape){ m_input_shape = t_shape; }
        void set_output_shape(LayerShape t_shape){ m_output_shape = t_shape; }
        LayerShape get_input_shape() const { return m_input_shape; }
        LayerShape get_output_shape() const { return m_output_shape; }

        void set_activation(const std::vector<float>&);
        virtual const std::vector<Matrix>& get_activation() const { return m_activation; }

        virtual float prev_agrad(int, int) const = 0;

        virtual void forward_propagation(const Layer&) = 0;
        virtual void back_propagation(const std::vector<float>&, const Layer&) = 0;
        virtual void back_propagation(const Layer&, const Layer&) = 0;

        virtual Layer* copy() const = 0;
    };
}

#endif//_MLL_LAYER_LAYER_HPP
