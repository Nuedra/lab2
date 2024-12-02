#ifndef COMPARE_HPP
#define COMPARE_HPP

#include <string>
#include "person.hpp"
#include "data_structures/ArraySequence.h"

template<typename T>
inline int compare_default(const T& a, const T& b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

inline int compare_person_first_name(const person& a, const person& b) {
    return compare_default(a.first_name, b.first_name);
}

inline int compare_person_last_name(const person& a, const person& b) {
    return compare_default(a.last_name, b.last_name);
}

inline int compare_person_birth_year(const person& a, const person& b) {
    return compare_default(a.birth_year, b.birth_year);
}

inline int compare_person_height(const person& a, const person& b) {
    return compare_default(a.height, b.height);
}

inline int compare_person_weight(const person& a, const person& b) {
    return compare_default(a.weight, b.weight);
}

inline int compare_person_salary(const person& a, const person& b) {
    return compare_default(a.salary, b.salary);
}

inline int compare_person_salary_lastname(const person& a, const person& b) {
    int result = compare_person_salary(a, b);
    if (result != 0) return result;
    return compare_person_last_name(a, b);
}

inline int compare_person_salary_lastname_height(const person& a, const person& b) {
    int result = compare_person_salary(a, b);
    if (result != 0) return result;
    result = compare_person_last_name(a, b);
    if (result != 0) return result;
    return compare_person_height(a, b);
}

#endif // COMPARE_HPP
