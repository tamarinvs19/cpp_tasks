#include <iostream>
#include <thread>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>

namespace lab_16 {

namespace inner {

template<class RandomIt, class Compare>
void expansion_merge(RandomIt first1, RandomIt last1, RandomIt last2, Compare comp = Compare()) {
    std::vector<typename std::iterator_traits<RandomIt>::value_type> merge_vec(last2 - first1);
    std::merge(first1, last1, last1, last2, merge_vec.begin(), comp);
    for (RandomIt i = merge_vec.begin(), j = first1; i < merge_vec.end(); ++i, ++j) {
	std::swap(*j, *i);
    }
}

template<class RandomIt, class Compare>
void merge_sort(RandomIt first, RandomIt last, Compare comp = Compare()) {
    if (last - first > 2) {
	std::size_t d_mid = (last - first)/2;

	merge_sort(first, first + d_mid, comp);
	merge_sort(first + d_mid, last, comp);
	expansion_merge(first, first + d_mid, last, comp);
    }
    else if (last - first == 2 && comp(*(last - 1), *first)) {
	std::swap(*(last - 1), *first);
    }
}

}

template<class RandomIt, class Compare>
void parallel_sort(std::size_t nthreads, RandomIt first, RandomIt last, Compare comp = Compare()) {
    std::vector<std::thread> vt;
    std::size_t step = (last - first) / nthreads;
    std::vector<RandomIt> borders(nthreads + 1);

    for (std::size_t i = 0; i <= nthreads; ++i) {
	if (i == nthreads)
	    borders[i] = last;
	else
	    borders[i] = first + i * step;
    }

    for (std::size_t i = 0; i < nthreads; ++i) {
	vt.emplace_back(inner::merge_sort<RandomIt, Compare>, borders[i], borders[i+1], comp);
    }

    for (std::size_t i = 0; i < nthreads; ++i) {
	vt[i].join();
	inner::expansion_merge(first, borders[i], borders[i+1], comp);
    }
}

template<class RandomIt>
void parallel_sort(std::size_t nthreads, RandomIt first, RandomIt last) {
    parallel_sort<RandomIt, std::less<>>(nthreads, first, last, std::less<>());
}

}

