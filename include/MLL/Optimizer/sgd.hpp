#ifndef SGD_HPP_INCLUDED
#define SGD_HPP_INCLUDED

#include<MLL/Optimizer/optimizer.hpp>

template<class T>
class SGD{};

template<Dense>
class SGD : public Optimizer<Dense>{
    public:
        SGD(float);

        void weight_cal (Matrix&, const Matrix&);

        void bias_cal (Matrix&, const Matrix&);
    };

#endif // SGD_HPP_INCLUDED
