#ifndef _MLL_LAYER_LAYERSHAPE_HPP
#define _MLL_LAYER_LAYERSHAPE_HPP

#include<initializer_list>
#include<iostream>

namespace MLL{
    struct LayerShape{
        int h;
        int w;
        int c;

        LayerShape() :
        h(0), w(0), c(0){}

        LayerShape(const std::initializer_list<int>& t_shape){
            if(t_shape.size() < 2){
                std::cout << "Not enough parameters in initializer list\n";
                exit(0);
            }

            std::vector<int> tmp;
            for(auto& i : t_shape) tmp.push_back(i);

            h = tmp[0];
            w = tmp[1];

            c = (tmp.size() < 3) ? 1 : tmp[2];
        }

        LayerShape(int t_h, int t_w, int t_c = 1) :
        h(t_h), w(t_w), c(t_c){}
    };
}

#endif//_MLL_LAYER_LAYERSHAPE_HPP
