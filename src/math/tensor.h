#ifndef TENSOR_H
#define TENSOR_H

#include <vector>
#include <ostream>
#include <vector>
#include <initializer_list>

namespace math {

template<typename T, size_t size>
class Tensor {
public:
    template<typename ...Args>
    Tensor(size_t first, Args&&... args) {
        this->data = std::vector<Tensor<T, size-1> >(first, Tensor<T, size-1>(args...));
    }

    Tensor<T, size-1>& operator[](size_t idx) {
        return this->data[idx];
    }

    const Tensor<T, size-1>& operator[](size_t idx) const {
        return this->data[idx];
    }

    Tensor<size_t, 2> shape() {
        Tensor<size_t, 2> rv(1, size);

        return rv;
    }

    friend std::ostream& operator<<(std::ostream& out, const Tensor& t) {
        out << "[ ";
        for(Tensor<T, size-1> tensor : t.data)
            out << tensor << ", ";
        out << "]";
        return out;
    }
private:
    std::vector<Tensor<T, size-1> > data;
};

template<typename T>
class Tensor<T, 1> {
public:
    Tensor(size_t size) : data(size) {}

    T& operator[](size_t idx) {
        return data[idx];
    }

    const T& operator[](size_t idx) const {
        return this->data[idx];
    }

    void assign(std::initializer_list<T> l) {
        this->data = l;
    }

    Tensor<size_t, 2> shape() {
        Tensor<size_t, 2> rv(1, 1);
        rv[0][0] = data.size();
        return rv;
    }

    friend std::ostream& operator<<(std::ostream& out, const Tensor<T, 1>& t) {
        out << "[ ";
        for(T val : t.data)
            out << val << ", ";
        out << "]";
        return out;
    }
private:
    std::vector<T> data;
};

} // namespace math

#endif