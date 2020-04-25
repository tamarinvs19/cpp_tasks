#include <iostream>
#include "huffman_test.h"

int main()
{
    huffman_test::HuffmanTreeTest test_tree;
    test_tree.run_all_tests();
    huffman_test::HuffmanArchiverTest test_arch;
    test_arch.run_all_tests();
    my_autotest::AutoTest::show_final_results();
    return 0;
}
