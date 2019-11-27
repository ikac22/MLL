#ifndef _MLL_NETWORK_NETWORK_HPP
#define _MLL_NETWORK_NETWORK_HPP

#include<vector>

#include<MLL/Layer/layer.hpp>

namespace MLL{
    class Network{
    private:
        std::vector< std::reference_wrapper<Layer> > m_layer;
    public:
        void add(const Layer& tl){ m_layer.push_back(*tl.copy()); }
        Layer& get_first(){ return m_layer[0]; }        // TODO: Remove
    };
}

#endif//_MLL_NETWORK_NETWORK_HPP
