#include<iostream>

#include<MLL/mll.hpp>
#include<mnist_parser/mnist_parser.hpp>

using namespace MLL;

int main(){
    auto tr_data = get_data("res/mnist/train-images-idx3-ubyte");
    auto tr_labels = get_labels("res/mnist/train-labels-idx1-ubyte");

    auto ev_data = get_data("res/mnist/t10k-images-idx3-ubyte");
    auto ev_labels = get_labels("res/mnist/t10k-labels-idx1-ubyte");

    Network net;

    //net.add(Conv2D(6, {3, 3}, Padding::same, 1, Activation::ReLU, {28, 28}));
    //net.add(Flatten());
    net.add(Input(784));
    net.add(Dense(16, Activation::ReLU));
    net.add(Dense(16, Activation::ReLU));
    net.add(Dense(10, Activation::Sigmoid));

    net.compile();
    //net.compile(Optimizer::SGD);

    net.fit(tr_data, tr_labels, 5);

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
