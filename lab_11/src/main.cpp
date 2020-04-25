#include "employees.h"
#include <fstream>
#include <iostream>

int main() {
    EmployeesArray employees_array = *(new EmployeesArray());
    std::string command;
    while (command != "exit") {
	std::cin >> command;
	if (command == "list") {
	    std::cout << employees_array;
	}
	else if (command == "add") {
	    int role;
	    std::cin >> role;
	    Employee * emp;
	    if (role == 1) {
		emp = new Developer(); 
	    }
	    else {
		emp = new SalesManager();
	    }
	    std::cin >> *emp;
	    employees_array.add(emp);
	}
	else if (command == "save") {
	    std::string file_name;
	    std::cin >> file_name;
	    std::ofstream f(file_name, std::ios::binary);
	    f << employees_array;
	    f.close();
	}
	else if (command == "load") {
	    std::string file_name;
	    std::cin >> file_name;
	    std::ifstream f(file_name, std::ios::binary);
	    f >> employees_array;
	    f.close();
	}
    }
    return 0;
}
