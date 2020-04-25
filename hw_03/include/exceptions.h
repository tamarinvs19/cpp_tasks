#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>

namespace my_exception {

class MyException: public std::logic_error {
    public:
	MyException(std::string s) : std::logic_error(s) {}
};

}

#endif
