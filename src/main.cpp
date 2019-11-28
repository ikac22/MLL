#include<iostream>

#include<MLL/mll.hpp>

using namespace MLL;

int main(){
    /*
    Matrix a(3, 3, {
        4, 9, 2,
        9, 2, 9,
        0, -1, 2
    });

    Matrix b(3, 3, {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    });

    Matrix c = f(a);
    Matrix d = f[a];

    c.output();

    std::cout << std::endl;

    d.output();
    */

    Network n;

    //n.add(Input(784));
    //n.add(Dense(0, 784, Activation::Linear));
    //n.add(Dense(784, 300, Activation::ReLU));
    //n.add(Dense(300, 150, Activation::ReLU));
    //n.add(Dense(150, 10, Actvation::Sigmoid));

    n.add(Input(784));
    n.add(Dense(300, Activation::ReLU));
    n.add(Dense(150, Activation::ReLU));
    n.add(Dense(10, Activation::Sigmoid));

    std::cout << n.get_first().get_size() << std::endl;


    return 0;
}

/*
void main_1(){
    std::vector<double> mnist_img;
    std::vector<int> mnist_label;

    Network<sequential> net;

    net.add(Layer::Input(784));
    net.add(Layer::Dense(300, Activation::ReLU));
    net.add(Layer::Dense(150, Activation::ReLU));
    net.add(Layer::Dense(10, Activation::Sigmoid));

    net.compile(Optimizer::Adagrad);

    net.train(mnist_img, mnist_label, {28, 28}, 60000);

    return 0;
}
*/
