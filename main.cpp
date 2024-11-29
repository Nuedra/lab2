#include <iostream>
#include "SmrtPtr.hpp"

struct Person {
    std::string first_name;
    std::string last_name;
    int birth_year;
    float height;
    float weight;

    std::string city;
    std::string phone;
    int salary;
};

template<typename T, typename Key>
int CompareByKey(const T& a, const T& b, Key T::*key) {
    if (a.*key < b.*key) {
        return -1;
    }
    if (a.*key > b.*key) {
        return 1;
    }
    return 0;
}

template<typename T>
int CompareDefault(const T& a, const T& b) {
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}



int main() {


    return 0;
}
