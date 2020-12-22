/*
Copyright 2021 Fixstars Corporation
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
http ://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iostream>
#include <chrono>
#include <string>

#include "matrix.hpp"
#include "conv_single.hpp"
#include "test.hpp"
#include "timer.hpp"

template<class Mat>
void conv(const Mat& A, const Mat& B, Mat& C,
        const std::size_t stride)
{
    /* Cの各要素についてのループ */
    /* Cを行単位で分割してスレッドを割り当てる */
    #pragma omp parallel for
    for (std::size_t c_i = 0; c_i < C.height(); ++c_i) {
        for (std::size_t c_j = 0; c_j < C.width(); ++c_j) {
            /* Bの各要素についてのループ */
            for (std::size_t b_i = 0; b_i < B.height(); ++b_i) {
                for (std::size_t b_j = 0; b_j < B.width(); ++b_j) {
                    const auto a_i = stride * c_i + b_i;
                    const auto a_j = stride * c_j + b_j;
                    C[c_i * C.width() + c_j]
                    += A[a_i * A.width() + a_j]
                    * B[b_i * B.width() + b_j];
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    const auto input_width = std::stoul(argv[1]);
    const auto input_height = std::stoul(argv[2]);
    const auto filter_width = std::stoul(argv[3]);
    const auto filter_height = std::stoul(argv[4]);
    const auto stride = std::stoul(argv[5]);
    const auto output_width = (input_width - filter_width + 1) / stride;
    const auto output_height = (input_height - filter_height + 1) / stride;
    Matrix<float> A(input_width, input_height);
    Matrix<float> B(filter_width, filter_height);
    Matrix<float> C_single(output_width, output_height);
    Matrix<float> C_multi(output_width, output_height);
    std::mt19937 rd(0);
    A.randomize(rd, -255, 255);
    B.randomize(rd, -255, 255);
    C_single.fill();
    const auto usec_single = timer<std::chrono::microseconds>([&A, &B, &C_single, &stride]() { conv_single(A, B, C_single, stride); } );
    C_multi.fill();
    const auto usec_multi = timer<std::chrono::microseconds>([&A, &B, &C_multi, &stride]() { conv(A, B, C_multi, stride); } );
    std::cout << "Single thread (usec): " << usec_single << std::endl;
    std::cout << "Multi thread (usec): " << usec_multi << std::endl;
    test(C_single, C_multi);
    return 0;
}
