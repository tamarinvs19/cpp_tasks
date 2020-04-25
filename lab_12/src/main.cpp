#include <iostream>

#include "my_vector.h"

namespace product {

class Product {
public:
    Product(const char* name, int quantity, double price);
    const char * name();
    int quantity();
    double price();
    friend std::ostream& operator<<(std::ostream&, Product&);
    friend std::ostream& operator<<(std::ostream&, const Product&);

private:
    const char *name_;  // Указатель владеет C-style строкой, на которую указывает.
    int quantity_;
    double price_;
};

const char * Product::name() {
    return name_;
}
int Product::quantity() {
    return quantity_;
}
double Product::price() {
    return price_;
}
Product::Product(const char* name, int quantity, double price) {
    name_ = name;
    quantity_ = quantity;
    price_ = price;
}

std::ostream& operator<<(std::ostream& os, const Product& p) {
    os << p.name_ << " " << p.quantity_ << " " << p.price_;
    return os;
}

void print(const my_vector::my_vector<Product>& v) {
    std::cout << v << std::endl;
}

}  // namespace product

int main() {
    // test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));
    // test_my_vector<int>(5, 10);

    return 0;
}
