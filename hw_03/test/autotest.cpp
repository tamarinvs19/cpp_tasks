#include <iostream>

#include "autotest.h"

namespace my_autotest {

int AutoTest::total_num = 0;
int AutoTest::failed_num = 0;

AutoTest::AutoTest() {}

void AutoTest::show_final_results() {
    std::cout << "Total tests: " << total_num << ". Failed: " << failed_num << std::endl;
}

void AutoTest::check(bool expr, const char *func, const char *filename, size_t line_num) {
    AutoTest::total_num ++;
    if (!expr) {
	std::cout << "Test failed! Error in file " << filename << ", function " << func << ", line " << line_num << std::endl;
	AutoTest::failed_num ++;
    }
}
}

