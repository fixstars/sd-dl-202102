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
#include "test.hpp"
#include "timer.hpp"

/* ReLU関数(並列化前) */
template<class Mat>
void relu_single(const Mat& A, Mat& B)
{
    for (std::size_t i = 0; i < A.height(); ++i) {
        for (std::size_t j = 0; j < A.width(); ++j) {
            const auto pos = i * A.width() + j;
            if (A[pos] <= 0) B[pos] = 0;
            else B[pos] = A[pos];
        }
    }
}

/* ReLU関数(並列化後) */
template<class Mat>
void relu(const Mat& A, Mat& B)
{
    /* ↓の1行を入れるだけ */
    #pragma omp parallel for
    for (std::size_t i = 0; i < A.height(); ++i) {
        for (std::size_t j = 0; j < A.width(); ++j) {
            const auto pos = i * A.width() + j;
            if (A[pos] <= 0) B[pos] = 0;
            else B[pos] = A[pos];
        }
    }
}

int main(int argc, char** argv)
{
    const auto width = std::stoul(argv[1]);
    const auto height = std::stoul(argv[2]);
    Matrix<float> A(width, height);
    Matrix<float> B_multi(width, height);
    Matrix<float> B_single(width, height);
    A.randomize(std::mt19937(0), -255, 255);
    const auto usec_single = timer<std::chrono::microseconds>([&A, &B_single]() { relu_single(A, B_single); } );
    const auto usec_multi = timer<std::chrono::microseconds>([&A, &B_multi]() { relu(A, B_multi); } );
    std::cout << "Single thread (usec): " << usec_single << std::endl;
    std::cout << "Multi thread (usec): " << usec_multi << std::endl;
    test(B_single, B_multi);
    return 0;
}
