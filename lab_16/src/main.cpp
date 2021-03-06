#include <iostream>
#include <vector>
#include <iterator>
#include "parallel_sort.hpp"

int main()
{
    std::vector<int> v = {5, 2, 8, 9, 4, 1};
    std::vector<int> sorted_v = {1, 2, 4, 5, 8, 9};
    std::vector<int> :: iterator beg = v.begin();
    std::vector<int> :: iterator end = v.end();
    lab_16::parallel_sort<std::vector<int>::iterator>(3, beg, end, [](int x, int y){return x > y;});
    for (auto i : v) {
	std::cout << i << " ";
    }
    return 0;
}
