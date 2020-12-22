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

#ifndef SD_DL_MATRIX_HPP
#define SD_DL_MATRIX_HPP

#include <type_traits>
#include <functional>
#include <memory>
#include <random>

template<typename T>
class BaseMatrix
{
    private:
    const std::size_t _width;
    const std::size_t _height;
    const std::unique_ptr<T[]> _ptr;
    public:
    BaseMatrix() noexcept : _width(0), _height(0) {}
    BaseMatrix(const std::size_t& width, const std::size_t& height) : _width(width), _height(height), _ptr(new T[width*height]) {}
    void assign(const std::function<T()>& f) {
        for (decltype(size()) i = 0; i < size(); ++i) {
            _ptr[i] = f();
        }
    }
    decltype(auto) operator[](const std::size_t& i) const { return _ptr[i]; }
    decltype(auto) width() const { return _width; }
    decltype(auto) height() const { return _height; }
    decltype(auto) size() const { return width() * height(); }
};

template<typename T>
class GenericMatrix : public virtual BaseMatrix<T> { };

template<typename T, typename Enable=void>
class RealMatrix : public virtual BaseMatrix<T> { };

template<typename T>
class RealMatrix<T, typename std::enable_if<std::is_floating_point<T>::value>::type> : public virtual BaseMatrix<T> {
    public:
    template<class RandomEngine>
    void randomize(RandomEngine&& rd, const T a, const T b) {
        std::uniform_real_distribution<T> dist(a, b);
        const auto& generator = [&dist, &rd](){ return dist(rd); };
        this->assign(generator);
    }
};

template<typename T>
class Matrix : public GenericMatrix<T>, public RealMatrix<T>
{
    public:
    Matrix(const std::size_t& width, const std::size_t& height) : BaseMatrix<T>(width, height) {}
    void fill(const T value=T()) {
        const auto& generator = [value](){ return value; };
        this->assign(generator);
    }
};

#endif
