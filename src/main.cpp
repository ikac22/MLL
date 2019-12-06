#include<iostream>

#include<MLL/mll.hpp>

using namespace MLL;

void debug(){

}

int main(){
    Network net;

    net.add(Input(784));
    net.add(Dense(300, Activation::ReLU));
    net.add(Dense(150, Activation::ReLU));
    net.add(Dense(10, Activation::Sigmoid));

    net.compile();
    //net.compile(Optimizer::SGD);

    //net.fit();

    //net.save_to_file("network.nd");

    for(int i = 0; i < net.m_layer_count; ++i){
        std::cout << net.m_layer[i].get().get_input_shape().h << " " <<
                     net.m_layer[i].get().get_input_shape().w << " " <<
                     net.m_layer[i].get().get_input_shape().c << std::endl <<
                     net.m_layer[i].get().get_output_shape().h << " " <<
                     net.m_layer[i].get().get_output_shape().w << " " <<
                     net.m_layer[i].get().get_output_shape().c << std::endl << std::endl;
    }

    const std::vector<float> input(784);
    auto res = net.predict(input);

    for(auto& e : res) std::cout << e << " ";
    std::cout << std::endl << res.size() << std::endl;

    return 0;
}
