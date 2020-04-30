#include <iostream>
#include <thread>
#include <iterator>
#include <algorithm>
#include <vector>

namespace lab_16 {

template<class RandomIt>
void merge_sort(RandomIt first, RandomIt last) {
    if (last - first > 2) {
	RandomIt middle = RandomIt((last + first) / 2);
	std::merge(first, middle, middle, last, first);
    }
    else if (last - first == 2 && *last < *first) {
	std::swap(*last, *first);
    }
}

template<class RandomIt>
void parallel_sort(std::size_t nthreads, RandomIt first, RandomIt last) {
    std::vector<std::thread> threads;
    std::size_t step = (last - first) / nthreads;
    for (std::size_t i = 0; i < nthreads; ++i) {
	threads.emplace_back(merge_sort, first + i * step, first + (i + 1) * step);
    }
    for (std::size_t i = 0; i < nthreads; i++) {
	threads[i].join();
	std::merge(first, first + i * step, first + i * step, first + i * step, first + (i + 1) * step);
    }
}

template<class RandomIt, class Compare>
void parallel_sort(std::size_t nthreads, RandomIt first, RandomIt last, Compare comp);


}

