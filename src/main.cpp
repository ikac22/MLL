#include<iostream>

#include<MLL/mll.hpp>
#include<mnist_parser/mnist_parser.hpp>

#ifdef __unix__

    #define TR_DATA_PATH "res/mnist/train-images-idx3-ubyte"
    #define TR_LABEL_PATH "res/mnist/train-labels-idx1-ubyte"
    #define EV_DATA_PATH "res/mnist/t10k-images-idx3-ubyte"
    #define EV_LABEL_PATH "res/mnist/t10k-labels-idx1-ubyte"

#elif defined(_WIN32) || defined(WIN64)

    #define TR_DATA_PATH "D:/Loznica/MLL/res/mnist/train-images-idx3-ubyte"
    #define TR_LABEL_PATH "D:/Loznica/MLL/res/mnist/train-labels-idx1-ubyte"
    #define EV_DATA_PATH "D:/Loznica/MLL/res/mnist/t10k-images-idx3-ubyte"
    #define EV_LABEL_PATH "D:/Loznica/MLL/res/mnist/t10k-labels-idx1-ubyte"

#endif

using namespace MLL;

int main(){

    auto tr_data = get_data(TR_DATA_PATH);
    auto tr_labels = get_labels(TR_LABEL_PATH);

    auto ev_data = get_data(EV_DATA_PATH);
    auto ev_labels = get_labels(EV_LABEL_PATH);

    //std::cout<<"Making network..."<<std::endl;
    Network net;

    //net.add(Conv2D(6, {3, 3}, Padding::same, 1, Activation::ReLU, {28, 28}));
    //net.add(Flatten());

    //std::cout<<"Adding input layer..."<<std::endl;
    net.add(Input(784));

    //std::cout<<"Adding 1st dense..."<<std::endl;
    net.add(Dense(16, Activation::Sigmoid));

    //std::cout<<"Adding 2nd dense..."<<std::endl;
    net.add(Dense(16, Activation::Sigmoid));

    //std::cout<<"Adding 3rd dense..."<<std::endl;
    net.add(Dense(10, Activation::Sigmoid));

    //std::cout<<"Compiling netwoek..."<<std::endl;
    net.compile();
    //net.compile(Optimizer::SGD);

    //std::cout<<"Fitting data..."<<std::endl;
    net.fit(tr_data, tr_labels, 5, 50);

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
