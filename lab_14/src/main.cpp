#include <iostream>
#include "matrix.h"

#include <exception>

void interface() {
    std::vector<matrix::Matrix> regs(10, matrix::Matrix());
    std::string command = "";
    size_t num, num2, nr, nc;
    char dollar;
    while (command != "exit") {
	try {
	std::cin >> command;
	if (command == "load") {
	    std::string file_name;
	    std::cin >> dollar >> num >> file_name;
	    try {
		regs[num].load(file_name);
	    }
	    catch (matrix_exception::LoadOpenException e) {
		std::cout << e.what() << std::endl;
	    }
	    catch (matrix_exception::LoadFormatException e) {
		std::cout << e.what() << std::endl;
	    }
	}
	if (command == "print") {
	    std::cin >> dollar >> num;
	    std::cout << regs[num];
	}
	if (command == "add") {
	    std::cin >> dollar >> num >> dollar >> num2;
	    try {
		regs[num].add(regs[num2]);
	    }
	    catch (matrix_exception::AddException e) {
		std::cout << e.what() << std::endl;
	    }
	}
	if (command == "mul") {
	    std::cin >> dollar >> num >> dollar >> num2;
	    try {
		regs[num].mul(regs[num2]);
	    }
	    catch (matrix_exception::MulException e) {
		std::cout << e.what() << std::endl;
	    }
	}
	if (command == "elem") {
	    try {
		std::cin >> dollar >> num >> nr >> nc;
		std::cout << regs[num].elem(nr, nc) << std::endl;
	    }
	    catch (matrix_exception::ElemException e) {
		std::cout << e.what() << std::endl;
	    }
	}
	}
	catch (std::bad_alloc e) {
	    std::cout << "Unable to allocate memory" << std::endl;
	}
    }
}

int main()
{
    interface();
    return 0;
}
