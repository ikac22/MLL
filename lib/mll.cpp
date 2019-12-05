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

OptimizerFunction::OptimizerFunction(Optimizer t_opt, float t_learning_rate,
                  float t_epsilon, float t_decay):
m_learning_rate(t_learning_rate),
m_epsilon(t_epsilon),
m_decay(t_decay){
    switch((int)t_opt){
        case 0: m_fun = SGD; break;
        case 1: m_fun = AdaGrad; break;
    }
}

Optimizers::SGD(){

}
}
