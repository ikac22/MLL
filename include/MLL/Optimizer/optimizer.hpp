#ifndef _MLL_OPTIMIZER_OPTIMIZER_HPP
#define _MLL_OPTIMIZER_OPTIMIZER_HPP

namespace MLL{
    enum class Optimizer{
        SGD,
        Adagrad
    };
    class OptimizerFunction{
        private:
            float m_learning_rate, m_epsilon, m_decay, ag_param;
            std::function<float(float, float)> m_fun;

            float SGD(float, float);
            float AdaGrad(float, float);
        protected:

        public:
            OptimizerFunction(Optimizer, float, float, float);

            float operator() (float, float);

            const Matrix operator() (const Matrix&, const Matrix&) const;
    };
}

#endif//_MLL_OPTIMIZER_OPTIMIZER_HPP
