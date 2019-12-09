#ifndef _MLL_NETWORK_NETWORK_HPP
#define _MLL_NETWORK_NETWORK_HPP

#include<vector>

#include<MLL/Layer/layer.hpp>

namespace MLL{
    class Network{
    public:
        std::vector< std::reference_wrapper<Layer> > m_layer;
        int m_layer_count;

        bool is_compiled = false;

        Layer& m_input_layer(){ return m_layer.front().get(); }
        Layer& m_output_layer(){ return m_layer.back().get(); }
    public:
        Network();

        void add(const Layer& tl){
            m_layer.push_back(*tl.copy());
            ++m_layer_count;
        }

        void compile();

        void fit(const std::vector<float>&, const std::vector<int>&);

        //void evaluate();

        const std::vector<float>& predict(const std::vector<float>&);

        //void load_from_file();
        //void save_to_file();
    };
}

#endif//_MLL_NETWORK_NETWORK_HPP
