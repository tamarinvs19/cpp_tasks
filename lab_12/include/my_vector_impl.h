#ifndef MY_VECTOR_IMPL_H_
#define MY_VECTOR_IMPL_H_

#include <memory>

namespace my_vector {

int get_min_capacity(int n) {
    int ln = 0;
    while ((1 << ln) < n)
	ln++;
    return 1 << ln;
}

template <typename T>
my_vector<T>::my_vector() {
    capacity_ = 1;
    size_ = 0;
}

template <typename T>
my_vector<T>::my_vector(std::size_t n) {
    capacity_ = get_min_capacity(n);
    size_ = n;
    array_ = (T*) new uint8_t [capacity_ * sizeof(T)];
    for (int i = 0; i < size_; i++) {
	new (array_+i) T();
    }
}

template <typename T>
my_vector<T>::~my_vector() {
    for (int i = 0; i < capacity_; i++) {
	array_[i].~T();
    }
    delete array_;
    delete size_;
    delete capacity_;
}

template <typename T>
std::size_t my_vector<T>::size() const {
    return size_;
}

template <typename T>
std::size_t my_vector<T>::capacity() const {
    return capacity_;
}

template <typename T>
bool my_vector<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void my_vector<T>::resize(std::size_t n) {
    if (n > capacity_) {
	reserve(n);
    }
    for (std::size_t i = size_; i<n; i++) {
	new (array_+i) T();
    }
    size_ = n;
}

template <typename T>
void my_vector<T>::reserve(std::size_t n) {
    if (capacity_ >= n) {
	return ;
    }
    capacity_ = get_min_capacity(n);
    T* new_array_ = (T*) new uint8_t [capacity_ * sizeof(T)];
    for (std::size_t i = 0; i < size_; i++) {
	new (new_array_+i) T();
	new_array_[i] = array_[i];
    }
    array_ = new_array_;
}

template <typename T>
void my_vector<T>::push_back(T t) {
    resize(size_ + 1);
    array_[size_] = new (array_ + size_) T(t);
}

template <typename T>
void my_vector<T>::pop_back() {
    if (empty())
	return ;
    array_[--size_].~T();
}

template <typename T>
void my_vector<T>::clear() {
    while (size_ > 0) {
	pop_back();
    }
}

template <typename T>
reference my_vector<T>::operator [](size_t j) { 
    return &array_[j];
}

template <typename T>
const_reference my_vector<T>::operator [](size_t j) const { 
    return &array_[j];
}

template <typename T>
my_vector<T>& my_vector<T>::operator=(my_vector<T>& other) {
    resize(other.size());
    for (size_t i = 0; i < other.size(); i++) {
	array_[i] = other.array_[i];
    }
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const my_vector<T>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
	os << vec[i] << " ";
    }
    return os;
}

}
#endif  // MY_VECTOR_IMPL_H_
