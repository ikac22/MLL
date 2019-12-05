#include<iostream>

#include<MLL/mll.hpp>

using namespace MLL;

int main(){
    Network net;

    net.add(Input(784));
    net.add(Dense(300, Activation::ReLU));
    net.add(Dense(150, Activation::ReLU));
    net.add(Dense(10, Activation::Sigmoid));

    net.compile(Optimizer::SGD);

    //net.fit();

    net.save_to_file("network.nd");

    return 0;
}
