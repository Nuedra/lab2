#ifndef SORT_COMPARISON_HPP
#define SORT_COMPARISON_HPP

#include <string>
#include "data_structures/ArraySequence.h"
#include "person.hpp"

ArraySequence<Person> load_persons_from_csv(const std::string& filename);
void compare_sorting_algorithms(const ArraySequence<Person>& persons, int (*cmp)(const Person&, const Person&));

#endif //SORT_COMPARISON_HPP
