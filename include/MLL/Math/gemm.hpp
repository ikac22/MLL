#ifndef _MLL_MATH_GEMM_HPP
#define _MLL_MATH_GEMM_HPP

#include<thread>

const static unsigned int thread_count = std::thread::hardware_concurrency();

namespace MLL{
    class Matrix;

    void gemm(const Matrix&, const Matrix&, Matrix&);

}

#endif//_MLL_MATH_GEMM_HPP
