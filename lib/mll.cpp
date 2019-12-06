#include<MLL/mll.hpp>

namespace MLL{

Matrix::Matrix(){ resize(0, 0); }

Matrix::Matrix(int t_height, int t_width){
    resize(t_height, t_width);
}

Matrix::Matrix(int t_height, int t_width,
               const std::vector<float>& t_init_list){
    resize(t_height, t_width);

    int k = 0;
    for(auto& elem : t_init_list){
        m_matrix[k / m_width][k % m_width] = elem;
        k++;
    }
}

Matrix& Matrix::operator=(const Matrix& t_matrix){
    resize(t_matrix.get_height(), t_matrix.get_width());

    for(int i = 0; i < m_height; ++i){
        for(int j = 0; j < m_width; ++j){
            m_matrix[i][j] = t_matrix[i][j];
        }
    }

    return *this;
}

void Matrix::resize(int t_height, int t_width){
    m_height = t_height;
    m_width = t_width;

    m_matrix.resize(m_height);
    for(auto& row : m_matrix) row.resize(m_width);
}

Matrix& operator+(const Matrix& t_matrix1, const Matrix& t_matrix2){
    if( t_matrix1.get_height() !=  t_matrix2.get_height() ||
        t_matrix1.get_width()  !=  t_matrix2.get_width() ){
        std::cout << "Unmatched matrix sizes : operator+" << std::endl;
        exit(0x901);
    }

    static Matrix result;
    result.resize(t_matrix1.get_height(), t_matrix1.get_width());

    for(int i = 0; i < result.get_height(); ++i){
        for(int j = 0; j < result.get_width(); ++j){
            result[i][j] = t_matrix1[i][j] + t_matrix2[i][j];
        }
    }

    return result;
}

Matrix& operator*(const Matrix& t_matrix1, const Matrix& t_matrix2){
    if(t_matrix1.get_width() != t_matrix2.get_height()){
        std::cout << "Unmatched matrix sizes : operator*" << std::endl;
        exit(0x902);
    }

    static Matrix result;
    result.resize(t_matrix1.get_height(), t_matrix2.get_width());

    gemm(t_matrix1, t_matrix2, result);

    return result;
}

const std::vector<float>& Matrix::to_array() const {
    static std::vector<float> result(m_height * m_width);
    int k = 0;

    for(int i = 0; i < m_height; ++i){
        for(int j = 0; j < m_width; ++j){
            result[k++] = m_matrix[i][j];
        }
    }

    return result;
}

void gemm(const Matrix& t_matrix1, const Matrix& t_matrix2, Matrix& result){
    for(int i = 0; i < result.get_height(); ++i){
        for(int j = 0; j < result.get_width(); ++j){
            for(int k = 0; k < t_matrix1.get_width(); ++k){
                result[i][j] += t_matrix1[i][k] * t_matrix2[k][j];
            }
        }
    }
}

ActivationFunction::ActivationFunction(Activation t_act){
    switch((int)t_act){
        case 0:{    // Linear
            m_activation_fun = Activations::linear_f;
            m_activation_deriv = Activations::linear_d;
        }break;
        case 1:{    // Sigmoid
            m_activation_fun = Activations::sigmoid_f;
            m_activation_deriv = Activations::sigmoid_d;
        }break;
        case 2:{    // ReLU
            m_activation_fun = Activations::relu_f;
            m_activation_deriv = Activations::relu_d;
        }break;
    }
}

float ActivationFunction::operator()(float x) const {
    return m_activation_fun(x);
}

float ActivationFunction::operator[](float x) const {
    return m_activation_deriv(x);
}

const Matrix& ActivationFunction::operator()(const Matrix& x) const {
    static Matrix result;
    result.resize(x.get_height(), x.get_width());

    for(int i = 0; i < result.get_height(); ++i){
        for(int j = 0; j < result.get_width(); ++j){
            result[i][j] = m_activation_fun(x[i][j]);
        }
    }

    return result;
}

const Matrix& ActivationFunction::operator[](const Matrix& x) const {
    static Matrix result;
    result.resize(x.get_height(), x.get_width());

    for(int i = 0; i < result.get_height(); ++i){
        for(int j = 0; j < result.get_width(); ++j){
            result[i][j] = m_activation_deriv(x[i][j]);
        }
    }

    return result;
}

namespace Activations{
    float linear_f(float x){ return x; }
    float linear_d(float x){ return 1; }
    float sigmoid_f(float x){ return 1 / (1 + exp(-x)); }
    float sigmoid_d(float x){ return sigmoid_f(x) * (1 - sigmoid_f(x)); }
    float relu_f(float x){ return x > 0 ? x : 0; }
    float relu_d(float x){ return x > 0; }
}

Layer::Layer(LayerShape t_output_shape) :
m_output_shape(t_output_shape){
    m_activation.resize(t_output_shape.c);

    for(auto& ch : m_activation) ch.resize(t_output_shape.h, t_output_shape.w);
}



CoreLayer::CoreLayer(int t_size) :
Layer(LayerShape(t_size, 1, 1)){

}

void CoreLayer::compile(){

}

Dense::Dense(int t_size, Activation t_act) :
CoreLayer(t_size),
m_fun(t_act){

}

void Dense::compile(){

}

void Dense::forward_propagation(const Layer& t_prev_layer){

}

void Dense::back_propagation(const Layer& t_prev_layer){

}

Flatten::Flatten() :
CoreLayer(0){}

void Flatten::compile(){
    int output_size = m_input_shape.h * m_input_shape.w * m_input_shape.c;
    m_output_shape = LayerShape(output_size, 1, 1);
}

void Flatten::forward_propagation(const Layer& t_prev_layer){
    int k = 0;
    for(auto& c : m_activation){
        for(int i = 0; i < c.get_height(); ++i){
            for(int j = 0; k < c.get_width(); ++j){
                m_activation[0][k++][0] = c[i][j];
            }
        }
    }
}

void Flatten::back_propagation(const Layer& t_prev_layer){

}

Input::Input(int t_size) :
CoreLayer(t_size){}

void Input::compile(){}

void Input::forward_propagation(const Layer& t_prev_layer){
    std::cout << "Error:" << std::endl;
    std::cout << "forward_propagation can't be called in Input layer" << std::endl;
}

void Input::back_propagation(const Layer& t_prev_layer){}

Network::Network() :
m_layer_count(0){}

void Network::compile(){
    m_layer[0].get().set_input_shape(m_layer[0].get().get_output_shape());

    for(int i = 1; i < m_layer_count; ++i){
        m_layer[i].get().set_input_shape(m_layer[i-1].get().get_output_shape());
    }

    for(int i = 0; i < m_layer_count; ++i){
        m_layer[i].get().compile();
    }
}

const std::vector<float>& Network::predict(const std::vector<float>& t_input){
    //m_input_layer().set_activation(t_input);  TODO: Implement set_activation

    for(int i = 1; i < m_layer_count; ++i){
        m_layer[i].get().forward_propagation(m_layer[i-1]);
    }

    return m_output_layer().get_activation()[0].to_array();
}



}
