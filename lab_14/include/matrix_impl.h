#ifndef MATRIX_IMPL_H_
#define MATRIX_IMPL_H_

#include "exception.h"
#include <fstream>

namespace matrix {
    Matrix::Matrix() {
	rows_ = 0;
	columns_ = 0;
	elements_ = std::vector< std::vector<int> >(0, std::vector<int>(0));
    }
    Matrix::Matrix(size_t rows, size_t columns) {
	rows_ = rows;
	columns_ = columns;
	elements_ = std::vector< std::vector<int> >(rows_, std::vector<int>(columns_, 0));
    }
    Matrix::~Matrix() {}

    int Matrix::elem(int i, int j) {
	if (i >= 0 && j >= 0 && i < (int)rows_ && j < (int)columns_) {
	    return elements_[i][j];
	}
	else {
	    throw matrix_exception::ElemException();
	}
    }
    size_t Matrix::rows() {
	return rows_;
    }
    size_t Matrix::columns() {
	return columns_;
    }

    void Matrix::add(Matrix& other) {
	if (!(
		    (this->rows_ == other.rows_) &&
		    (this->columns_ == other.columns_)
	     )) {
	    throw matrix_exception::AddException();
	}
	std::vector< std::vector<int> > sum(this->rows_, std::vector<int>(this->columns_, 0));
	for (size_t i=0; i<this->rows(); i++)
	    for (size_t j=0; j<this->columns(); j++)
		sum[i][j] = this->elem(i, j) + other.elem(i, j);
	elements_ = sum;
    }
    void Matrix::mul(Matrix& other) {
	if (this->columns_ != other.rows_) {
	    throw matrix_exception::MulException();
	}
	std::vector< std::vector<int> > mul(this->rows_, std::vector<int>(other.columns_, 0));
	for (size_t i=0; i<this->rows(); i++)
	    for (size_t j=0; j<other.columns(); j++)
		for (size_t k=0; k<this->columns(); k++)
		    mul[i][j] += this->elem(i, k) * other.elem(k, j);
	columns_ = other.columns();
	elements_ = mul;
    }
    void Matrix::load(std::string file_name) {
	std::ifstream f(file_name);
	if (!f.is_open()) {
	    throw matrix_exception::LoadOpenException();
	}
	size_t rows, columns;
	f >> rows >> columns;
	if (rows != 0 && columns != 0 && f.tellg() == -1) {
	    throw matrix_exception::LoadFormatException();
	}
	std::vector< std::vector<int> > m(rows, std::vector<int>(columns, 0));
	for (size_t i=0; i<rows; i++)
	    for (size_t j=0; j<columns; j++) {
		if (f.tellg() == -1) {
		    throw matrix_exception::LoadFormatException();
		}
		f >> m[i][j];
	    }
	columns_ = columns;
	rows_ = rows;
	elements_ = m;
    }
    std::ostream& operator<<(std::ostream& os, Matrix& m) {
	for (size_t i=0; i<m.rows(); i++) {
	    for (size_t j=0; j<m.columns(); j++) {
		os << m.elements_[i][j] << " ";
	    }
	    os << std::endl;
	}
	return os;
    }

} // matrix

#endif // MATRIX_IMPL_H_
