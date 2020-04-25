#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <iostream>
#include <cassert>
#include <cstdint>
#include <cmath>

template<typename T, std::size_t N>
class my_array {
    public:
	my_array();
	~my_array();
	T& at(std::size_t index);
	const T& at(std::size_t index) const;
	T& operator[](std::size_t index);
	const T& operator[](std::size_t index) const;

	bool empty() const ;
	std::size_t size() const ;

	void fill(T val);
    private:
	T* array_;
};

template<std::size_t N>
class my_array<bool, N> {
    class proxy;
    public:
	my_array();
	~my_array();

	proxy at(std::size_t index) {
	    assert(N > index);
	    return proxy(array_[index / 8], 1 << index % 8);
	}
	bool at(std::size_t index) const {
	    assert(N > index);
	    return (bool)proxy(array_[index / 8], 1 << index % 8);
	}

	proxy operator[](std::size_t index) {
	    std::cout << index << std::endl;
	    std::cout << sizeof(array_) << std::endl;
	    std::cout << (1 << index % 8) << std::endl;
	    return proxy(array_[index / 8], 1 << index % 8);
	}
	bool operator[](std::size_t index) const {
	    std::cout << "proxy2" << std::endl;
	    return array_[index / 8] & (1 << (index % 8));
	}

	bool empty() const ;
	std::size_t size() const ;

	void fill(bool val);
    private:
	uint8_t array_[N / 8 + (1 ? N % 8 != 0 : 0)];
};

template<std::size_t N>
class my_array<bool, N>::proxy {
    public:
	proxy(uint8_t& data, uint8_t msk) : data_(data), msk_(msk) {
	};
	operator bool() const {
	    return (bool)data_ & msk_;
	}

	proxy& operator = (bool b) {
	    std::cout << data_ << std::endl;
	    std::cout << msk_ << std::endl;
	    if (b)
		data_ |= msk_;
	    else
		data_ &= -msk_;
	    return *this;
	}

	proxy& operator = (const proxy& other) {
	    return *this = (bool) other;
	}
    private:
	uint8_t& data_;
	uint8_t msk_;
};

#include "my_array_impl.h"

#endif  // MY_ARRAY_H_
