#ifndef _MLL_LAYER_LAYERSHAPE_HPP
#define _MLL_LAYER_LAYERSHAPE_HPP

namespace MLL{
    struct LayerShape{
        int h;
        int w;
        int c;

        LayerShape(){}
        LayerShape(int t_h, int t_w, int t_c) :
        h(t_h), w(t_w), c(t_c){}
    };
}

#endif//_MLL_LAYER_LAYERSHAPE_HPP
