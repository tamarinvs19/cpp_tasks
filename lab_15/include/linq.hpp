#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iterator>
#include <iostream>
#include <type_traits>

namespace linq {

template<typename T, typename Iter>
class range_enumerator;

template<typename T>
class drop_enumerator;

template<typename T>
class take_enumerator;

template<typename T, typename U, typename F>
class select_enumerator;

template<typename T, typename F>
class until_enumerator;

template<typename T, typename F>
class where_enumerator;

template<typename T>
class enumerator {
    public:
	virtual ~enumerator() = default;
	virtual const T& operator*() const = 0; // Получает текущий элемент.
	virtual enumerator& operator++() = 0;  // Переход к следующему элементу
	virtual operator bool() const = 0;  // Возвращает true, если есть текущий элемент

	auto take(int count) {
	    return take_enumerator<T>(*this, count);
	}

	auto drop(int count) {
	    return drop_enumerator<T>(*this, count);
	}

	template<typename U = T, typename F>
	auto select(F func) {
	    return select_enumerator<U, T, F>(*this, std::move(func));
	}

	template<typename F>
	auto until(F func) {
	    return until_enumerator<T, F>(*this, std::move(func));
	}

	auto until_eq(const T& t) {
	    return until([&t](const T& x){return x == t;});
	}

	template<typename F>
	auto where(F func) {
	    return where_enumerator<T, F>(*this, std::move(func));
	}

	auto where_neq(const T& t) {
	    return where([&t](const T& x){return x != t;});
	}

	std::vector<T> to_vector() {
	    std::vector<T> result;
	    while(*this) {
		result.push_back(**this);
		++*this;
	    }
	    return result;
	}

	template<typename Iter>
	void copy_to(Iter it) {
	    while (*this) {
		*it = **this;
		++it;
		++*this;
	    }
	}
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
    public:
	range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}
	
	const T& operator* () const {
	    return *begin_;
	}

	range_enumerator& operator++() {
	    ++begin_;
	    return *this;
	}

	operator bool() const {
	    return begin_ != end_;
	}

    private:
	Iter begin_, end_;
};

template<typename T>
auto from(T begin, T end) {
    return range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

template<typename T>
class take_enumerator : public enumerator<T> {
    public:
	take_enumerator(enumerator<T>& parent, int count) : parent_(parent), count_(count) {}

	const T& operator* () const override {
	    return *parent_;
	}

	take_enumerator& operator++() override {
	    --count_;
	    if (count_ > 0)
		++parent_;
	    return *this;
	}

	operator bool() const override {
	    return count_ > 0 && (bool) parent_;
	}

    private:
	enumerator<T>& parent_;
	int count_;
};

template<typename T>
class drop_enumerator : public enumerator<T> {
    public:
	drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
	    for (int i = 0; i < count; ++i)
		++*this;
	}

	const T& operator* () const override {
	    return *parent_;
	}

	drop_enumerator& operator++() override {
	    ++parent_;
	    return *this;
	}

	operator bool() const override {
	    return parent_;
	}

    private:
	enumerator<T>& parent_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
    public:
	select_enumerator(enumerator<U> &parent, F func) : parent_(parent), func_(func) {}
	~select_enumerator() {
	    delete res;
	}
	
	const T& operator* () const override {
	    if (res != nullptr)
		res->~T();
	    res = new T(func_(*parent_));
	    return *res;
	}

	select_enumerator& operator++() override {
	    ++parent_;
	    return *this;
	}

	operator bool() const override {
	    return parent_;
	}

    private:
	enumerator<U>& parent_;
	mutable F func_;
	mutable T* res = nullptr;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
    public:
	until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(predicate) {}

	const T& operator* () const override {
	    return *parent_;
	}

	until_enumerator& operator++() override {
	    ++parent_;
	    return *this;
	}

	operator bool() const override {
	    return parent_ && !(predicate_(*parent_));
	}

    private:
	enumerator<T>& parent_;
	mutable F predicate_;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
    public:
	where_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(predicate) {
	    while (parent_ && !predicate_(*parent_))
		++*this;
	}

	const T& operator* () const override {
	    return *parent_;
	}

	where_enumerator& operator++() override {
	    ++parent_;
	    while (parent_ && !predicate_(*parent_))
		++parent_;
	    return *this;
	}

	operator bool() const override {
	    return parent_;
	}

    private:
	enumerator<T>& parent_;
	mutable F predicate_;
};

} // namespace linq

#endif
