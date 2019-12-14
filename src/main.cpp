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

    Network net;

    //net.add(Conv2D(6, {3, 3}, Padding::same, 1, Activation::ReLU, {28, 28}));
    //net.add(Flatten());
    net.add(Input(784));
    net.add(Dense(300, Activation::Sigmoid));
    net.add(Dense(100, Activation::Sigmoid));
    net.add(Dense(10, Activation::Sigmoid));
    net.compile();
    //net.compile(Optimizer::SGD);

    net.fit(tr_data, tr_labels, 12, 50);

    //net.save_to_file("network.nd");

    return 0;
}
