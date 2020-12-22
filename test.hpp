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

#ifndef SD_DL_TEST_HPP
#define SD_DL_TEST_HPP

#include <type_traits>
#include <iostream>
#include <limits>

template <class Mat>
bool test(const Mat& A, const Mat& B)
{
    using T = typename std::remove_reference<decltype(A[0])>::type;
    const auto eps = std::numeric_limits<T>::epsilon();
    std::cout << "Validation...";
    if (A.width() != B.width() || A.height() != B.height()) {
        std::cout << "Failed" << std::endl;
        return false;
    }
    for (std::size_t i = 0; i < A.height(); ++i) {
        for(std::size_t j = 0; j < A.width(); ++j) {
            const auto idx = i * A.width() + j;
            if (std::abs(A[idx] - B[idx]) > eps) {
                std::cout << "Failed" << std::endl;
                return false;
            }
        }
    }
    std::cout << "Success" << std::endl;
    return true;
}

#endif
