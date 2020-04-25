#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <tuple>
#include "huffman_test.h"
#include "tree.h"
#include "huffman.h"

namespace huffman_test {

HuffmanTreeTest::HuffmanTreeTest() {}

void HuffmanTreeTest::run_all_tests() {
    test_tree_node_constructor();
    test_tree_node_compar_operator();
    test_huff_tree_build_1();
    test_huff_tree_build_2();
    test_huff_tree_build_3();
    test_huff_tree_gen_relative_code_1();
    test_huff_tree_gen_relative_code_2();
    test_huff_tree_get_root_1();
    test_huff_tree_get_root_2();
    test_huff_tree_get_code_table_1();
    test_huff_tree_get_code_table_2();
}

void HuffmanTreeTest::test_tree_node_constructor() {
    huffman_tree::TreeNode* n1 = new huffman_tree::TreeNode();
    huffman_tree::TreeNode* n2 = new huffman_tree::TreeNode('a', 100);
    huffman_tree::TreeNode n3 = huffman_tree::TreeNode('b', 2, n1, n2);
    DO_CHECK(n1->value_ == ' ' && n1->weight_ == 0);
    DO_CHECK(n2->value_ == 'a' && n2->weight_ == 100);
    DO_CHECK(n3.value_ == 'b' && n3.weight_ == 2 && n3.left_children_ == n1 && n3.right_children_ == n2);
}

void HuffmanTreeTest::test_tree_node_compar_operator() {
    huffman_tree::TreeNode* n1 = new huffman_tree::TreeNode('e', 1);
    huffman_tree::TreeNode* n2 = new huffman_tree::TreeNode('a', 100);
    huffman_tree::TreeNode n3 = huffman_tree::TreeNode('b', 4, n1, n2);
    DO_CHECK(&n2 > &n1);
}

void HuffmanTreeTest::test_huff_tree_build_3() {
    std::vector<int> stat_table = {0, 1, 2};
    huffman_tree::HuffTree ht;
    ht.build(stat_table);
    DO_CHECK(ht.get_root()->weight_ == 3);
    DO_CHECK(ht.get_root()->left_children_->weight_ == 1);
    DO_CHECK(ht.get_root()->left_children_->left_children_->weight_ == 0);
    DO_CHECK(ht.get_root()->left_children_->right_children_->weight_ == 1);
    DO_CHECK(ht.get_root()->right_children_->weight_ == 2);
}

void HuffmanTreeTest::test_huff_tree_build_2() {
    std::vector<int> stat_table = {1, 2};
    huffman_tree::HuffTree ht;
    ht.build(stat_table);
    DO_CHECK(ht.get_root()->weight_ == 3);
    DO_CHECK(ht.get_root()->left_children_->weight_ == 1);
    DO_CHECK(ht.get_root()->right_children_->weight_ == 2);
}

void HuffmanTreeTest::test_huff_tree_build_1() {
    std::vector<int> stat_table = {1};
    huffman_tree::HuffTree ht;
    ht.build(stat_table);
    DO_CHECK(ht.get_root()->weight_ == 1);
    DO_CHECK(ht.get_root()->left_children_ == 0);
    DO_CHECK(ht.get_root()->right_children_ == 0);
}

void HuffmanTreeTest::test_huff_tree_gen_relative_code_1() {
    std::vector<int> stat_table = {0, 1, 2};
    huffman_tree::HuffTree ht;
    ht.build(stat_table);
    ht.gen_relative_code(ht.get_root());
    std::unordered_map<char, std::string> code_table = *(ht.get_code_table());

    DO_CHECK(code_table[0] == "00");
    DO_CHECK(code_table[1] == "01");
    DO_CHECK(code_table[2] == "1");
}

void HuffmanTreeTest::test_huff_tree_gen_relative_code_2() {
    std::vector<int> stat_table = {0, 1};
    huffman_tree::HuffTree ht;
    ht.build(stat_table);
    ht.gen_relative_code(ht.get_root());
    std::unordered_map<char, std::string> code_table = *(ht.get_code_table());

    DO_CHECK(code_table[0] == "0");
    DO_CHECK(code_table[1] == "1");
}

void HuffmanTreeTest::test_huff_tree_get_root_1() {
    std::vector<int> stat_table = {0, 1, 2};
    huffman_tree::HuffTree ht;
    ht.build(stat_table);
    huffman_tree::TreeNode* root = ht.get_root();

    DO_CHECK(root->weight_ == 3 && root->value_ == ' '); 
    DO_CHECK(root->left_children_->weight_ == 1 );
    DO_CHECK(root->right_children_->weight_ == 2 );
}

void HuffmanTreeTest::test_huff_tree_get_root_2() {
    std::vector<int> stat_table = {3, 1};
    huffman_tree::HuffTree ht;
    ht.build(stat_table);
    ht.gen_relative_code(ht.get_root());

    huffman_tree::TreeNode* root = ht.get_root();

    DO_CHECK(root->weight_ == 4 && root->value_ == ' '); 
    DO_CHECK(root->left_children_->weight_ == 1 );
    DO_CHECK(root->right_children_->weight_ == 3 );
}

void HuffmanTreeTest::test_huff_tree_get_code_table_1() {
    std::vector<int> stat_table = {0, 1, 2};
    huffman_tree::HuffTree ht;
    ht.build(stat_table);
    ht.gen_relative_code(ht.get_root());
    std::unordered_map<char, std::string> code_table = *(ht.get_code_table());

    DO_CHECK(code_table[0] == "00");
    DO_CHECK(code_table[1] == "01");
    DO_CHECK(code_table[2] == "1");
    DO_CHECK(code_table[3] == "");
    DO_CHECK(code_table[100] == "");
}

void HuffmanTreeTest::test_huff_tree_get_code_table_2() {
    std::vector<int> stat_table = {3, 4};
    huffman_tree::HuffTree ht;
    ht.build(stat_table);
    ht.gen_relative_code(ht.get_root());
    std::unordered_map<char, std::string> code_table = *(ht.get_code_table());

    DO_CHECK(code_table[0] == "0");
    DO_CHECK(code_table[1] == "1");
}

HuffmanArchiverTest::HuffmanArchiverTest() {}

void HuffmanArchiverTest::run_all_tests() {
    test_arch_constructor();
    test_arch_calculate_statistic();
    test_arch_calculate_statistic_equal_symbs();
    test_arch_calculate_statistic_empty_file();
    test_arch_save_statistic_1();
    test_arch_save_statistic_2();
    test_arch_read_statistic_1();
    test_arch_read_statistic_2();
    test_arch_archivate_random_symbs();
    test_arch_archivate_many_equal_symbs();
    test_arch_archivate_emply_file();
    test_arch_archivate_few_lines();
    test_arch_get_info_after_unarchivate();
    test_arch_get_info_after_archivate();
}

void HuffmanArchiverTest::test_arch_constructor() {
    std::ofstream fin = std::ofstream("constr_in.test_file", std::ostream::binary);
    fin << "test file\n12345\n    \n +_)(*&^%$#@!\n\n";
    fin.close();
    huffman_archiver::HuffmanArchiver ha = huffman_archiver::HuffmanArchiver("constr_in.test_file", "constr_out.test_file");
    DO_CHECK(ha.file_in_.is_open());
    DO_CHECK(ha.file_out_.is_open());
    DO_CHECK(ha.additional_memory_size == 0);
    DO_CHECK(ha.stat_table_.size() == huffman_archiver::HuffmanArchiver::DICT_SIZE);
}
void HuffmanArchiverTest::test_arch_calculate_statistic() {
    std::ofstream fin = std::ofstream("stat_in.test_file", std::ostream::binary);
    fin << "test file ";
    fin.close();
    huffman_archiver::HuffmanArchiver ha = huffman_archiver::HuffmanArchiver("stat_in.test_file", "stat_out.test_file");
    ha.calculate_statistic();
    DO_CHECK(
	    ha.stat_table_[(int)'t'] == 2 &&
	    ha.stat_table_[(int)'e'] == 2 &&
	    ha.stat_table_[(int)'s'] == 1 &&
	    ha.stat_table_[(int)' '] == 3 &&
	    ha.stat_table_[(int)'f'] == 1 &&
	    ha.stat_table_[(int)'i'] == 1 &&
	    ha.stat_table_[(int)'l'] == 1);
}
void HuffmanArchiverTest::test_arch_calculate_statistic_equal_symbs() {
    std::ofstream fin = std::ofstream("stat_in_2.test_file", std::ostream::binary);
    fin << "tttttttttt";
    fin.close();
    huffman_archiver::HuffmanArchiver ha = huffman_archiver::HuffmanArchiver("stat_in_2.test_file", "stat_out.test_file");
    ha.calculate_statistic();
    DO_CHECK(ha.stat_table_[(int)'t'] == 11);
}
void HuffmanArchiverTest::test_arch_calculate_statistic_empty_file() {
    std::ofstream fin = std::ofstream("stat_in.test_file", std::ostream::binary);
    fin << "";
    fin.close();
    huffman_archiver::HuffmanArchiver ha = huffman_archiver::HuffmanArchiver("stat_in.test_file", "stat_out.test_file");
    ha.calculate_statistic();
    DO_CHECK(ha.stat_table_[(int)'t'] == 0);
}

void HuffmanArchiverTest::test_arch_save_statistic_1() {
    huffman_archiver::HuffmanArchiver* ha = new huffman_archiver::HuffmanArchiver("stat_in.test_file", "stat_out.test_file");
    ha->stat_table_ = {1, 2, 3};
    ha->save_statistic();
    delete ha;
    std::ifstream f = std::ifstream("stat_out.test_file", std::istream::binary);
    int a, b, c;
    f >> a >> b >> c;
    DO_CHECK(a == 1 && b == 2 && c == 3);
    f.close();
}

void HuffmanArchiverTest::test_arch_save_statistic_2() {
    huffman_archiver::HuffmanArchiver *ha = new huffman_archiver::HuffmanArchiver("stat_in.test_file", "stat_out.test_file");
    ha->stat_table_ = {0, 100000};
    ha->save_statistic();
    delete ha;
    std::ifstream f = std::ifstream("stat_out.test_file", std::istream::binary);
    int a, b;
    f >> a >> b;
    DO_CHECK(a == 0 && b == 100000);
    f.close();
}

void HuffmanArchiverTest::test_arch_read_statistic_1() {
    huffman_archiver::HuffmanArchiver *ha = new huffman_archiver::HuffmanArchiver("stat_in.test_file", "stat_out.test_file");
    ha->stat_table_ = std::vector<int> (256, 2);
    ha->save_statistic();
    delete ha;
    huffman_archiver::HuffmanArchiver *ha1= new huffman_archiver::HuffmanArchiver("stat_out.test_file", "stat_in.test_file");
    ha->read_statistic();
    DO_CHECK(
	    ha1->stat_table_[0] == 2 &&
	    ha1->stat_table_[1] == 2 &&
	    ha1->stat_table_[255] == 2);
    delete ha1;
}

void HuffmanArchiverTest::test_arch_read_statistic_2() {
    huffman_archiver::HuffmanArchiver *ha = new huffman_archiver::HuffmanArchiver("stat_in.test_file", "stat_out.test_file");
    ha->stat_table_ = std::vector<int> (256, 0);
    ha->save_statistic();
    delete ha;
    huffman_archiver::HuffmanArchiver *ha1 = new huffman_archiver::HuffmanArchiver("stat_out.test_file", "stat_in.test_file");
    ha->read_statistic();
    DO_CHECK(
	    ha1->stat_table_[0] == 0 &&
	    ha1->stat_table_[1] == 0 &&
	    ha1->stat_table_[255] == 0);
    delete ha1;
}

void HuffmanArchiverTest::test_arch_archivate_random_symbs() {
    std::ofstream f = std::ofstream("test_in.test_file");
    std::string ts = "qwertyuiop[]':lkjhgfdsazxcvbnm,./?><MNBVCXZASDFGHJKL;/}{POIUYTREWQ!@#$%^&*()_+";
    f << ts;
    f.close();

    huffman_archiver::HuffmanArchiver *ha = new huffman_archiver::HuffmanArchiver("test_in.test_file", "test_out.test_file");
    ha->archivate();
    delete ha;
    huffman_archiver::HuffmanArchiver *ha1 = new huffman_archiver::HuffmanArchiver("test_out.test_file", "test_in1.test_file");
    ha->unarchivate();
    delete ha1;
    std::ifstream fout = std::ifstream("test_in1.test_file");
    std::string out; 
    fout >> out;
    DO_CHECK(out == ts);
}

void HuffmanArchiverTest::test_arch_archivate_many_equal_symbs() {
    std::ofstream f = std::ofstream("test_in.test_file");
    std::string ts = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    f << ts;
    f.close();

    huffman_archiver::HuffmanArchiver *ha = new huffman_archiver::HuffmanArchiver("test_in.test_file", "test_out.test_file");
    ha->archivate();
    delete ha;
    huffman_archiver::HuffmanArchiver *ha1 = new huffman_archiver::HuffmanArchiver("test_out.test_file", "test_in1.test_file");
    ha1->unarchivate();
    delete ha1;
    std::ifstream fout = std::ifstream("test_in1.test_file");
    std::string out; 
    fout >> out;
    DO_CHECK(out == ts);
    fout.close();
}

void HuffmanArchiverTest::test_arch_archivate_emply_file() {
    std::ofstream f = std::ofstream("test_in.test_file");
    std::string ts = "";
    f << ts;
    f.close();

    huffman_archiver::HuffmanArchiver *ha = new huffman_archiver::HuffmanArchiver("test_in.test_file", "test_out.test_file");
    ha->archivate();
    delete ha;
    huffman_archiver::HuffmanArchiver *ha1 = new huffman_archiver::HuffmanArchiver("test_out.test_file", "test_in1.test_file");
    ha1->unarchivate();
    delete ha1;
    std::ifstream fout = std::ifstream("test_in1.test_file");
    std::string out; 
    fout >> out;
    DO_CHECK(out == ts);
    fout.close();
}

void HuffmanArchiverTest::test_arch_archivate_few_lines() {
    std::ofstream f = std::ofstream("test_in.test_file");
    std::string ts = "aaa\nbbb\nccc\ndddd";
    f << ts;
    f.close();

    huffman_archiver::HuffmanArchiver *ha = new huffman_archiver::HuffmanArchiver("test_in.test_file", "test_out.test_file");
    ha->archivate();
    delete ha;
    huffman_archiver::HuffmanArchiver *ha1 = new huffman_archiver::HuffmanArchiver("test_out.test_file", "test_in1.test_file");
    ha1->unarchivate();
    delete ha1;
    std::ifstream fout = std::ifstream("test_in1.test_file");
    std::string out; 
    fout >> out;
    DO_CHECK(out == "aaa");
    fout >> out;
    DO_CHECK(out == "bbb");
    fout >> out;
    DO_CHECK(out == "ccc");
    fout >> out;
    DO_CHECK(out == "dddd");
    fout.close();
}
void HuffmanArchiverTest::test_arch_get_info_after_archivate() {
    std::ofstream f = std::ofstream("test_in.test_file");
    std::string ts = "aaaa";
    f << ts;
    f.close();

    huffman_archiver::HuffmanArchiver *ha = new huffman_archiver::HuffmanArchiver("test_in.test_file", "test_out.test_file");
    ha->archivate();
    std::tuple <int, int, int> info = ha->get_info();
    DO_CHECK(
	    std::get<0>(info) == 4 &&
	    std::get<1>(info) == 522 &&
	    std::get<2>(info) == 512
	    );
    delete ha;
}

void HuffmanArchiverTest::test_arch_get_info_after_unarchivate() {
    std::ofstream f = std::ofstream("test_in.test_file");
    std::string ts = "aaaa";
    f << ts;
    f.close();

    huffman_archiver::HuffmanArchiver *ha = new huffman_archiver::HuffmanArchiver("test_in.test_file", "test_out.test_file");
    ha->archivate();
    delete ha;
    huffman_archiver::HuffmanArchiver *ha1 = new huffman_archiver::HuffmanArchiver("test_out.test_file", "test_in1.test_file");
    ha1->unarchivate();
    std::tuple <int, int, int> info = ha1->get_info();
    DO_CHECK(
	    std::get<0>(info) == 522 &&
	    std::get<1>(info) == 4 &&
	    std::get<2>(info) == 512
	    );
    delete ha1;
}
}
