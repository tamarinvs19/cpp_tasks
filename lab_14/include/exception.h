#ifndef EXTENTION_H_
#define EXTENTION_H_

namespace matrix_exception {
class MatrixException {
    public:
	MatrixException(std::string s) {
	    msg_ = s;
	}
	const char * what() const noexcept {
	    return msg_.c_str();
	}
    private:
	std::string msg_;
};

class LoadOpenException : public MatrixException {
    public:
	LoadOpenException(): MatrixException("LOAD: unable to open file.") {}
};

class LoadFormatException : public MatrixException {
    public:
	LoadFormatException(): MatrixException("LOAD: invalid file format.") {}
};

class AddException : public MatrixException {
    public:
	AddException(): MatrixException("ADD: dimension do not match.") {}
};

class MulException : public MatrixException {
    public:
	MulException(): MatrixException("MUL: #arg1.columns != #arg2.rows.") {}
};

class ElemException : public MatrixException {
    public:
	ElemException(): MatrixException("ACCESS: bad index.") {}
};
} // matrix_exception

#endif // EXTENTION_H_
