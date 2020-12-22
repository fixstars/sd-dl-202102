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

#ifndef SD_DL_CONV_SINGLE_HPP
#define SD_DL_CONV_SINGLE_HPP

#include "matrix.hpp"

template<class Mat>
void conv_single(const Mat& A, const Mat& B, Mat& C,
        const std::size_t stride)
{
    /* Bの各要素についてのループ */
    for (std::size_t b_i = 0; b_i < B.height(); ++b_i) {
        for (std::size_t b_j = 0; b_j < B.width(); ++b_j) {
            /* Aの各要素についてのループ */
            for (std::size_t a_i = b_i; (a_i - b_i + B.height()) <= A.height(); a_i += stride) {
                for (std::size_t a_j = b_j; (a_j - b_j + B.width()) <= A.width(); a_j += stride) {
                    const auto c_i = (a_i - b_i) / stride;
                    const auto c_j = (a_j - b_j) / stride;
                    C[c_i * C.width() + c_j]
                        += A[a_i * A.width() + a_j]
                        * B[b_i * B.width() + b_j];
                }
            }
        }
    }
}

#endif
