#include "bin_manip.h"
#include <cassert>
#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>

std::ofstream& operator<<(std::ofstream& os, const write_le_int32& d) {
    static_assert(CHAR_BIT == 8);
    static_assert(sizeof(d.data) == 4);
    for (std::size_t i = 0; i < sizeof(d.data); ++i) {
	char chunk = (d.data >> (i * CHAR_BIT)) & 0xFF;
	os.write(&chunk, sizeof(char));
    }
    return os;
}

std::ifstream& operator>>(std::ifstream& is, const read_le_int32 &d) {
    static_assert(CHAR_BIT == 8);
    static_assert(sizeof(d.data) == 4);

    d.data = 0;
    for (std::size_t i = 0; i < sizeof(d.data); ++i) {
	int32_t chunk = 0;
	is.read((char *)&chunk, sizeof(char));
	d.data |= chunk << (i * CHAR_BIT);
    }
    return is;
}

std::ofstream& operator<<(std::ofstream& os, const write_bool& d) {
    os.put(d.data ? 1 : 0);
    return os;
}

std::ifstream& operator>>(std::ifstream& is, const read_bool &d) {
    d.data = is.get();
    return is;
}

std::ofstream& operator<<(std::ofstream& os, const write_c_str& d) {
    os.write(d.data, std::strlen(d.data) + 1);
    return os;
}

std::ifstream& operator>>(std::ifstream& is, const read_c_str& d) {
    for (std::size_t i = 0;; i++) {
	assert(i < d.size);
	char c = is.get();
	if (!is) {
	    d.data[i] = 0;
	    return is;
	}
	d.data[i] = c;
	if (!c) return is;

	if (i + 1 >= d.size) {
	    d.data[i] = 0;
	    is.setstate(std::ios_base::failbit);
	}
    }
    return is;
}
