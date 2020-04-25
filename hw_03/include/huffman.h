#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <tuple>

#include "tree.h"

namespace huffman_test {
class HuffmanArchiverTest;
}

namespace huffman_archiver {
#define once

class HuffmanArchiver {
    friend class huffman_test::HuffmanArchiverTest;
    private:
	static const int DICT_SIZE = 256;
	size_t additional_memory_size;

	std::ifstream file_in_;
	std::ofstream file_out_;
	std::vector<int> stat_table_;

	huffman_tree::HuffTree* huff_tree_;

	void read_statistic();
	void save_statistic();
	void calculate_statistic();
    public:
	HuffmanArchiver(const std::string file_in_name, const std::string file_out_name);
	~HuffmanArchiver();

	void archivate();
	void unarchivate();
	std::tuple<int, int, int> get_info();
};
}
#endif
