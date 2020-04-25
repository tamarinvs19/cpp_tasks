#ifndef _AUTOTEST_H_
#define _AUTOTEST_H_
#include <cstddef>

#define DO_CHECK(EXPR) my_autotest::AutoTest::check(EXPR, __func__, __FILE__, __LINE__);

namespace my_autotest {
class AutoTest {
    public:
	AutoTest();
	virtual void run_all_tests()=0;
	static void show_final_results();

	static void check(bool expr, const char *func, const char *filename, size_t line_num);
    protected:
	static int failed_num;
	static int total_num;

};
}


#endif
