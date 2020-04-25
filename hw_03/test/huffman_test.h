#ifndef _HUFFMAN_TEST_H_
#define _HUFFMAN_TEST_H_

#include "autotest.h"

namespace huffman_test {
#define once

class HuffmanTreeTest : public my_autotest::AutoTest {
    public:
	HuffmanTreeTest();
	void run_all_tests() override;
    private:
	void test_tree_node_constructor();
	void test_tree_node_compar_operator();
	
	void test_huff_tree_build_1();
	void test_huff_tree_build_2();
	void test_huff_tree_build_3();
	void test_huff_tree_gen_relative_code_1();
	void test_huff_tree_gen_relative_code_2();
	void test_huff_tree_get_root_1();
	void test_huff_tree_get_root_2();
	void test_huff_tree_get_code_table_1();
	void test_huff_tree_get_code_table_2();
};

class HuffmanArchiverTest : public my_autotest::AutoTest {
    public:
	HuffmanArchiverTest();
	void run_all_tests() override;
    private:
	void test_arch_constructor();
	void test_arch_calculate_statistic();
	void test_arch_calculate_statistic_equal_symbs();
	void test_arch_calculate_statistic_empty_file();
	void test_arch_save_statistic_1();
	void test_arch_save_statistic_2();
	void test_arch_read_statistic_1();
	void test_arch_read_statistic_2();
	void test_arch_archivate_random_symbs();
	void test_arch_archivate_many_equal_symbs();
	void test_arch_archivate_emply_file();
	void test_arch_archivate_few_lines();
	void test_arch_get_info_after_archivate();
	void test_arch_get_info_after_unarchivate();
};
}

#endif
