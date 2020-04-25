#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#pragma once
#include "bin_manip.h"
#include <stdint.h>
#include <ostream>
#include <istream>
#include <sstream>
#include <cstring>
#include <vector>
#include <iostream>

class Employee {
    public:
	virtual int get_base_salary() const;
	virtual char * get_name() const;
	virtual int salary() const;
	virtual std::istream& set_info(std::istream& is)=0;
	virtual std::ostream& get_info(std::ostream& os)=0;
	virtual std::ifstream& set_bin_info(std::ifstream& os)=0;
	virtual std::ofstream& get_bin_info(std::ofstream& os)=0;
	friend std::ostream& operator<<(std::ostream&, Employee&);
	friend std::istream& operator>>(std::istream&, Employee&);
	friend std::ofstream& operator<<(std::ofstream&, Employee&);
	friend std::ifstream& operator>>(std::ifstream&, Employee&);
	Employee();
	// ~Employee();
    protected:
	int32_t MAX_LEN = 100;
	char* _name;
	int32_t _base_salary;
};
class Developer: public Employee {
    public:
	int salary() const;
	bool get_has_bonus() const;

	std::istream& set_info(std::istream& is);
	std::ostream& get_info(std::ostream& os);
	std::ifstream& set_bin_info(std::ifstream& os);
	std::ofstream& get_bin_info(std::ofstream& os);

	Developer (char * name, int32_t base_salary, bool has_bonus);
	Developer ();
	// ~Developer ();
    private:
	bool _has_bonus;
};

class SalesManager: public Employee {
    public:
	int salary() const;
	int get_sold_nm() const;
	int get_price() const;
	void sold_nm(int32_t sold_nm);
	void price(int32_t price);

	std::ostream& get_info(std::ostream& os);
	std::istream& set_info(std::istream& os);
	std::ofstream& get_bin_info(std::ofstream& os);
	std::ifstream& set_bin_info(std::ifstream& is);

	SalesManager (char* name, int32_t base_salary, int32_t sold_nm, int32_t price);
	SalesManager();
	// ~SalesManager();
    private:
	int32_t _sold_nm, _price;
};

class EmployeesArray {
    public:
	void add(Employee* e);
	std::vector <Employee*> get_employees();
	int get_count_emplyees();
	int total_salary() const;

	friend std::ostream& operator<<(std::ostream&, EmployeesArray&);
	friend std::ofstream& operator<<(std::ofstream&, EmployeesArray&);
	friend std::ifstream& operator>>(std::ifstream&, EmployeesArray&);
	EmployeesArray(std::vector<Employee*> employees);
	EmployeesArray();
	// ~EmployeesArray();
    private:
	std::vector <Employee*> _employees;
};

#endif
