#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <cstddef>
#include <vector>
#include <string>

namespace matrix {
class Matrix {
    public:
	Matrix();
	Matrix(size_t, size_t);
	~Matrix();
	void load(std::string file_name);
	friend std::ostream& operator<<(std::ostream&, Matrix&);

	void add(Matrix&);
	void mul(Matrix&);
	int elem(int, int);

	size_t rows();
	size_t columns();
    private:
	int rows_, columns_;
	std::vector<std::vector<int> > elements_;
};
} // matrix


#include "matrix_impl.h"

#endif // MATRIX_H_
