#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <iostream>

namespace my_vector {

template<typename T>
class my_vector {
public:
    my_vector();
    my_vector(std::size_t n);
    my_vector(my_vector<T>& other);
    my_vector<T>& operator=(my_vector<T>&);
    ~my_vector();

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    void resize(std::size_t n);
    void reserve(std::size_t n);

    reference operator[](std::size_type index);
    const_reference operator[](std::size_type index) const;
    // T& operator[](std::size_t index);
    // const T& operator[](std::size_t index) const;

    void push_back(T t);
    void pop_back();
    void clear();

private:
    size_t capacity_;
    size_t size_;
    T* array_;
};

template <typename T>
std::ostream& operator<<(std::ostream&, const my_vector<T>&);

}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_
