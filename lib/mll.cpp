#include<MLL/mll.hpp>

#include<vector>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<time.h>
#include<thread>
#include<chrono>
#include<random>
#include<sstream>
#include<iomanip>

#ifdef __unix__
    #define OS_WIN false
#elif defined(_WIN32) || defined(WIN64)
    #define OS_WIN true
    #include<windows.h>
#endif

namespace MLL{
///MATRIX
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

const Matrix& operator+(const Matrix& t_matrix1, const Matrix& t_matrix2){
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

const Matrix& operator*(const Matrix& t_matrix1, const Matrix& t_matrix2){
    if(t_matrix1.get_width() != t_matrix2.get_height()){
        std::cout << "Unmatched matrix sizes : operator*" << std::endl;
        exit(0x902);
    }

    static Matrix result;
    result.resize(t_matrix1.get_height(), t_matrix2.get_width());

    for(int i = 0; i < result.get_height(); ++i){
        for(int j = 0; j < result.get_width(); ++j){
            for(int k = 0; k < t_matrix1.get_width(); ++k){
                result[i][j] += t_matrix1[i][k] * t_matrix2[k][j];
            }
        }
    }

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

float get_kernel_sum(const std::vector<Matrix>& t_prev_activation,
                     const std::vector<Matrix>& t_kernels,
                     LayerShape t_kernel_size,
                     float t_bias, int ti, int tj){
    float res = 0;
    int pi = t_kernel_size.h / 2;
    int pj = t_kernel_size.w / 2;

    for(int c = 0; c < t_prev_activation.size(); ++c){
        for(int i = 0; i < t_kernel_size.h; ++i){
            for(int j = 0; j < t_kernel_size.w; ++j){
                res += t_kernels[c][i][j]*t_prev_activation[c][ti+i-pi][tj+j-pj];
            }
        }
    }
    res += t_bias;

    return res;
}

///GRADIENT

void Gradient<Dense>::set_size(int h, int w){
    m_weight.resize(h, w);
    m_activation.resize(h, 1);
    m_bias.resize(h, 1);
}

///ACT_FUN

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

#define PBSTR "============================================================"
#define PBWIDTH 60

void loading_bar(float percent, int cur_epoch, int total_epoch,
                 int correct, int g, float cost_sum){
    if(OS_WIN) system("CLS");
    int val = (int) (percent * 100);
    int lpad = (int) (percent * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    float loss = 1 - (correct / (float)g);
    float avg_cost = cost_sum / (float)g;
    printf("\rEpoch %d/%d : [%.*s>%*s] %3d%%  Loss: %.*f Avg cost: %.*f  ", cur_epoch,
           total_epoch, lpad, PBSTR, rpad, "", val, 4, loss, 4, avg_cost);
    fflush(stdout);
}

int get_max_position(const std::vector<float>& t_vect){
    int p = 0;
    for(int i = 1; i < t_vect.size(); ++i){
        if(t_vect[i] > t_vect[p]){
            p = i;
        }
    }

    return p;
}

///LAYER

Layer::Layer(LayerShape t_output_shape) :
m_output_shape(t_output_shape){
    m_activation.resize(t_output_shape.c);
    m_sum.resize(t_output_shape.c);

    for(auto& ch : m_activation) ch.resize(t_output_shape.h, t_output_shape.w);
    for(auto& ch : m_sum) ch.resize(t_output_shape.h, 1);
}

void Layer::set_activation(const std::vector<float>& t_activation){
    int k = 0;
    for(int c = 0; c < m_activation.size(); ++c){
        for(int i = 0; i < m_activation[c].get_height(); ++i){
            for(int j = 0; j < m_activation[c].get_width(); ++j){
                m_activation[c][i][j] = t_activation[k++];
            }
        }
    }
}

Dense::Dense(int t_size, Activation t_act):
Layer({t_size, 1, 1}),
m_fun(t_act){
}

///DENSE

void Dense::compile(){
    m_bias.resize(m_output_shape.h, 1);
    m_weight.resize(m_output_shape.h, m_input_shape.h);

    m_gradient.set_size(m_output_shape.h, m_input_shape.h);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(0.0, 1.0);

    double coef = sqrt(1 / (double)(m_input_shape.h));
    for(int i = 0; i < m_weight.get_height(); ++i){
        for(int j = 0; j < m_weight.get_width(); ++j){
            m_weight[i][j] = distribution(generator) * coef;
        }
    }
}

float Dense::prev_agrad(int i, int j) const{
    return m_weight[j][i] * m_fun[m_sum[0][j][0]] * m_gradient.a()[j][0];
}

void Dense::forward_propagation(const Layer& t_prev_layer){
    m_sum[0] = m_weight * t_prev_layer.get_activation()[0] + m_bias;
    m_activation[0] = m_fun(m_sum[0]);
}

void Dense::back_propagation(const std::vector<float>& t_target,
                             const Layer& t_prev_layer){
    // TODO: Calculate the gradient of output layer with given target values

    //std::cout<<"    -Making refferences..."<<std::endl;
    auto& agrad = m_gradient.get_a();
    auto& wgrad = m_gradient.get_w();
    auto& bgrad = m_gradient.get_b();
    auto& prev_act = t_prev_layer.get_activation();

    //std::cout<<"    -Starting for..."<<std::endl;
    for(int i = 0; i < t_target.size() ;i++){

        //std::cout<<"        -Cycle "<<i<<"..."<<std::endl<<"        -AGRAD..."<<std::endl;
        agrad[i][0] = 2 * (m_activation[0][i][0] - t_target[i]);
        //std::cout<<"        -WGRAD..."<<std::endl;
        for(int j = 0; j < m_input_shape.h ;j++){
            //std::cout<<"            -Cycle "<<j<<"..."<<std::endl;
            wgrad[i][j] = prev_act[0][j][0] * m_fun[m_sum[0][i][0]] * agrad[i][0];
        }
        //std::cout<<"        -BGRAD..."<<std::endl;
        bgrad[i][0] = m_fun[m_sum[0][i][0]] * agrad[i][0];
    }
}

void Dense::back_propagation(const Layer& t_next_layer,
                             const Layer& t_prev_layer){
    auto& agrad = m_gradient.get_a();
    auto& wgrad = m_gradient.get_w();
    auto& bgrad = m_gradient.get_b();
    auto& prev_act = t_prev_layer.get_activation();

    for(int i = 0; i < m_output_shape.h ;i++){
        agrad[i][0] = 0;

        for(int j = 0; j < t_next_layer.get_output_shape().h ;j++)
            agrad[i][0] = t_next_layer.prev_agrad(i, j);

        for(int j = 0; j < m_input_shape.h ;j++)
            wgrad[i][j] = prev_act[0][j][0] * m_fun[m_sum[0][i][0]] * agrad[i][0];

        bgrad[i][0] = m_fun[m_sum[0][i][0]] * agrad[i][0];
    }

}

void Dense::output() const{
    std::cout<<std::endl;
    std::cout<<std::left<<std::setw(13)<<"Activations: ";
    for(int i = 0; i < m_output_shape.h ;i++)
        std::cout<<std::left<<std::setw(6)<<std::setprecision(3)<<m_activation[0][i][0];
}

void Dense::apply_gradient(){
    for(int i = 0; i < m_weight.get_height(); ++i){
        for(int j = 0; j < m_weight.get_width(); ++j){
            m_weight[i][j] -= m_gradient.w()[i][j];
        }
    }

    for(int i = 0; i < m_bias.get_height(); ++i){
        m_bias[i][0] -= m_gradient.b()[i][0];
    }
}

///FLATTEN

Flatten::Flatten() :
Layer({0, 1, 1}){}

void Flatten::compile(){
    int output_size = m_input_shape.h * m_input_shape.w * m_input_shape.c;
    set_output_shape({output_size, 1, 1});
    m_activation[0].resize(output_size, 1);
}

float Flatten::prev_agrad(int i, int j) const{
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

void Flatten::back_propagation(const std::vector<float>& t_target,
                               const Layer& t_prev_layer){}
void Flatten::back_propagation(const Layer& t_next_layer,
                               const Layer& t_prev_layer){}


///INPUT

Input::Input(int t_size) :
Layer({t_size, 1, 1}){}

void Input::compile(){
    set_input_shape(m_output_shape);
}

float Input::prev_agrad(int i, int j) const{
}

void Input::forward_propagation(const Layer& t_prev_layer){
    std::cout << "Error: \n";
    std::cout << "Input::forward_propagation called\n";
    exit(0);
}

void Input::output() const{
    std::cout<<std::endl;
    std::cout<<std::left<<std::setw(13)<<"Activations: ";
    for(int i = 0; i < m_output_shape.h ;i++)
        std::cout<<std::left<<std::setw(6)<<std::setprecision(3)<<m_activation[0][i][0];
}
///CONV2D

Conv2D::Conv2D(int t_kernel_count, LayerShape t_kernel_size, Padding t_pad,
               int t_stride, Activation t_act, LayerShape t_input_shape) :
Layer({0, 1, 1}),
m_kernel_count(t_kernel_count),
m_kernel_size(t_kernel_size),
m_stride(t_stride),
m_fun(t_act){
    if(t_pad == Padding::same)
        m_pad_size = (std::max(m_kernel_size.h, m_kernel_size.w) - 1) / 2;
    else
        m_pad_size = 0;

    set_input_shape(t_input_shape);
}

void Conv2D::compile(){
    LayerShape is = get_input_shape();
    set_output_shape(LayerShape(
        (is.h - m_kernel_size.h + 2 * m_pad_size) / m_stride + 1,
        (is.w - m_kernel_size.w + 2 * m_pad_size) / m_stride + 1,
        m_kernel_count
    ));

    m_bias.resize(m_kernel_count);
    m_kernel.resize(m_kernel_count);
    for(int i = 0; i < m_kernel_count; ++i){
        m_kernel[i].resize(get_input_shape().c);
        for(int j = 0; j < get_input_shape().c; ++j){
            m_kernel[i][j].resize(m_kernel_size.h, m_kernel_size.w);
        }
    }

    m_activation.resize(m_kernel_count);
    for(int c = 0; c < m_kernel_count; ++c){
        m_activation[c].resize(get_output_shape().h, get_output_shape().w);
    }
}

float Conv2D::prev_agrad(int i, int j) const{
}

void Conv2D::forward_propagation(const Layer& t_prev_layer){
    int p = m_pad_size;
    for(int c = 0; c < m_kernel_count; ++c){
        for(int i = 0; i < get_output_shape().h; ++i){
            for(int j = 0; j < get_output_shape().w; ++j){
                m_activation[c][i][j] = get_kernel_sum(
                    t_prev_layer.get_activation(),
                    m_kernel[c],
                    m_kernel_size,
                    m_bias[c],
                    p+i, p+j
                );
                // TODO: Implement get_kernel_sum
            }
        }
    }
}

void Conv2D::back_propagation(const std::vector<float>& t_target,
                              const Layer& t_prev_layer){}
void Conv2D::back_propagation(const Layer& t_next_layer,
                              const Layer& t_prev_layer){}

///NETWORK

Network::Network() :
m_layer_count(0){}

void Network::compile(){
    m_layer[0].get().compile();

    for(int i = 1; i < m_layer_count; ++i){
        m_layer[i].get().set_input_shape(m_layer[i-1].get().get_output_shape());
        m_layer[i].get().compile();
    }

    is_compiled = true;
}

const std::vector<float>& Network::predict(const std::vector<float>& t_input){
    m_input_layer().set_activation(t_input);

    for(int i = 1; i < m_layer_count; ++i){
        m_layer[i].get().forward_propagation(m_layer[i-1]);
    }

    return m_output_layer().get_activation()[0].to_array();
}

void Network::fit(std::vector<float>& t_data,
                  std::vector<int>& t_labels,
                  int t_epoch_count,
                  int t_subset_size){
    if(!is_compiled){
        std::cout << "Can't fit uncompiled model!" << std::endl;
        exit(0);
    }

    int data_size = t_data.size();
    int iter_count = t_labels.size();
    LayerShape input_shape = m_input_layer().get_input_shape();
    int input_size = input_shape.h * input_shape.w * input_shape.c;
    LayerShape output_shape = m_output_layer().get_output_shape();
    int output_size = output_shape.h * output_shape.w * output_shape.c;

    //std::cout<<"Start training..."<<std::endl;
    for(int e = 0; e < t_epoch_count; ++e){
        int correct = 0;
        float cost_sum = 0;

        //std::cout<<"Suffleing data..."<<std::endl;
        shuffle_data(t_data, t_labels);

        //std::cout<<"Backprop state..."<<std::endl;
        for(int i = 0; i < iter_count; ++i){
            //std::cout<<"Making iter_input..."<<std::endl;
            std::vector<float> iter_input(t_data.begin() + i * input_size,
                                          t_data.begin() + (i+1) * input_size);

            auto res = predict(iter_input);

            std::cout<<"Result guess "<<i<<": "<<get_max_position(res)<<std::endl;

            //std::cout<<"Making target array..."<<std::endl;
            std::vector<float> target(output_size);
            target[t_labels[i]] = 1;

            //std::cout<<"Getting cost..."<<std::endl;
            cost_sum += get_cost(target, res);
            if(get_max_position(res) == t_labels[i]) ++correct;

            //std::cout<<"Backprop output..."<<std::endl;
            m_output_layer().back_propagation(target,
                                              m_layer[m_layer_count - 2].get());
            //std::cout<<"Backprop middle..."<<std::endl;
            for(int j = m_layer_count - 2; j > 0; --j){
                m_layer[j].get().back_propagation(m_layer[j+1].get(),
                                                  m_layer[j-1].get());
            }

            //std::cout<<"Loading bar..."<<std::endl;
            loading_bar((i+1) / (float)iter_count, e + 1, t_epoch_count,
                        correct, i, cost_sum);

            //for(auto& l : m_layer) l.get().output();

            m_output_layer().output();

            //std::cout<<"Applying grads..."<<std::endl;

            if(!(i % t_subset_size))
                for(auto& l : m_layer) l.get().apply_gradient();
        }

        for(auto& l : m_layer) l.get().apply_gradient();
        std::cout << std::endl;
    }
}

float Network::get_cost(const std::vector<float>& t_target,
                        const std::vector<float>& t_output){
    float res = 0;
    for(int i = 0; i < t_target.size(); ++i){
        res += pow(t_target[i] - t_output[i], 2);
    }
    return res;
}

void Network::shuffle_data(std::vector<float>& t_data, std::vector<int>& t_label){
    std::vector<int> index(t_label.size());
    for(int i = 0; i < index.size(); ++i){
        index[i] = i;
    }

    std::random_shuffle(index.begin(), index.end());

    std::vector<float> data_sh(t_data.size());
    std::vector<int> label_sh(t_label.size());

    LayerShape is = m_input_layer().get_input_shape();
    int input_size = is.h * is.w * is.c;

    for(int i = 0; i < index.size(); ++i){
        label_sh[i] = t_label[index[i]];

        for(int j = 0; j < input_size; ++j){
            data_sh[i * input_size + j] = t_data[index[i] * input_size + j];
        }
    }

    t_data = data_sh;
    t_label = label_sh;
}

}
