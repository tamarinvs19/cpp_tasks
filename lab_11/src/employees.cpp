#include "employees.h"
#include "bin_manip.h"
#include <cstring>
#include <fstream>
#include <iostream>

Employee::Employee() {
    _name = new char[MAX_LEN];
}
// Employee::~Employee() {
//     delete &MAX_LEN;
//     delete &_name;
//     delete &_base_salary;
// }

int Employee::get_base_salary() const {
    return _base_salary;
};
char* Employee::get_name() const {
    return _name;
};
int Employee::salary() const {
    return get_base_salary();
};

std::ostream& operator<<(std::ostream& os, Employee& employee) {
    employee.get_info(os);
    return os;
}
std::ofstream& operator<<(std::ofstream& os, Employee& employee) {
    employee.get_bin_info(os);
    return os;
}
std::istream& operator>>(std::istream& is, Employee& employee) {
    employee.set_info(is);
    return is;
}
std::ifstream& operator>>(std::ifstream& is, Employee& employee) {
    employee.set_bin_info(is);
    return is;
}


Developer::Developer (char * name, int32_t base_salary, bool has_bonus) {
    _name = name;
    _base_salary = base_salary;
    _has_bonus = has_bonus;
}
Developer::Developer () {
    _name = new char[MAX_LEN];
}
// Developer::~Developer () {
    // delete &MAX_LEN;
    // delete &_name;
    // delete &_base_salary;
    // delete &_has_bonus;
// }

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}
bool Developer::get_has_bonus() const {
    return _has_bonus;
};

std::ostream& Developer::get_info(std::ostream& os) {
    os <<
	"Developer" << std::endl <<
	"Name: " << get_name() << std::endl <<
	"Base Salary: " << get_base_salary() << std::endl <<
	"Has bonus: " << (get_has_bonus() ? "+" : "-") << std::endl;
    return os;
};
std::istream& Developer::set_info(std::istream& is) {
    is >> 
	_name >>
	_base_salary >> 
	_has_bonus;
    return is;
}
std::ofstream& Developer::get_bin_info(std::ofstream& os) {
    os << 
	write_le_int32(1) <<
	write_c_str(_name) <<
	write_le_int32(_base_salary) <<
	write_bool(_has_bonus);
    return os;
}
std::ifstream& Developer::set_bin_info(std::ifstream& is) {
    is >>
	read_c_str(_name, sizeof(_name)) >>
	read_le_int32(_base_salary) >>
	read_bool(_has_bonus);
    return is;
};


SalesManager::SalesManager (char* name, int32_t base_salary, int32_t sold_nm, int32_t price) {
    _name = name;
    _base_salary = base_salary;
    _sold_nm = sold_nm;
    _price = price;
}
SalesManager::SalesManager () {
    _name = new char[MAX_LEN];
}
// SalesManager::~SalesManager () {
//     delete &_name;
//     delete &_base_salary;
//     delete &_sold_nm;
//     delete &_price;
// }

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}
int SalesManager::get_sold_nm() const {
    return _sold_nm;
}
int SalesManager::get_price() const {
    return _price;
}
void SalesManager::sold_nm(int32_t sold_nm) { 
    _sold_nm = sold_nm; 
}
void SalesManager::price(int32_t price) {
    _price = price; 
}

std::ostream& SalesManager::get_info(std::ostream& os) {
    os <<
	"Sales Manager" << std::endl <<
	"Name: " << get_name() << std::endl <<
	"Base Salary: " << get_base_salary() << std::endl <<
	"Sold items: " << get_sold_nm() << std::endl <<
	"Item price: " << get_price() << std::endl;
    return os;
};
std::istream& SalesManager::set_info(std::istream& is) {
    is >> 
	_name >> 
	_base_salary >> 
	_sold_nm >> 
	_price;
    return is;
}
std::ofstream& SalesManager::get_bin_info(std::ofstream& os) {
    os <<
	write_le_int32(2) <<
	write_c_str(_name) <<
	write_le_int32(_base_salary) <<
	write_le_int32(_sold_nm) <<
	write_le_int32(_price);
    return os;
};
std::ifstream& SalesManager::set_bin_info(std::ifstream& is) {
    is >>
	read_c_str(_name, sizeof(_name)) >>
	read_le_int32(_base_salary) >>
	read_le_int32(_sold_nm) >>
	read_le_int32(_price);
    return is;
};


EmployeesArray::EmployeesArray (std::vector<Employee*> employees) {
    std::vector<Employee*> _employees;
    for (Employee* e: employees) {
	add(e);
    }
}
EmployeesArray::EmployeesArray () {
    std::vector<Employee*> _employees;
}
// EmployeesArray::~EmployeesArray () {
    // delete &_employees;
    // for (auto e: _employees) {
	// std::cout << *e;
	// delete &e;
    // }
// }

void EmployeesArray::add(Employee* e) {
    _employees.push_back(e);
}
std::vector <Employee*> EmployeesArray::get_employees() {
    return _employees;
}
int EmployeesArray::get_count_emplyees() {
    return _employees.size();
}
int EmployeesArray::total_salary() const {
    int32_t total_salary = 0;
    for (Employee* e: _employees) {
	total_salary += e->salary();
    }
    return total_salary;
}
std::ostream& operator<<(std::ostream& os, EmployeesArray& employees_array) {
    std::vector <Employee*> emps = employees_array.get_employees();
    for (int32_t i=0; i<(int32_t)emps.size(); i++) {
	os << i + 1 << ". ";
	emps[i]->get_info(os);
    }
    os << "== Total salary: " << employees_array.total_salary() << "\n\n";
    return os;
}
std::ofstream& operator<<(std::ofstream& os, EmployeesArray& employees_array) {
    std::vector <Employee*> emps = employees_array.get_employees();
    os << write_le_int32(emps.size());
    for (int32_t i=0; i<(int32_t)emps.size(); i++) {
	emps[i]->get_bin_info(os);
    }
    return os;
}
std::ifstream& operator>>(std::ifstream& is, EmployeesArray& employees_array) {
    int32_t cnt;
    is >> read_le_int32(cnt);
    for (int i=0; i<cnt; i++) {
	int32_t role;
	is >> read_le_int32(role);
	Employee * emp;
	if (role == 1) {
	    emp = new Developer(); 
	}
	else {
	    emp = new SalesManager();
	}
	is >> *emp;
	employees_array.add(emp);
    }
    return is;
}

