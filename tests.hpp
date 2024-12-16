#ifndef TESTS_HPP
#define TESTS_HPP

#include "BubbleSorter.hpp"
#include "HeapSorter.hpp"
#include "InsertionSorter.hpp"
#include "QuickSorter.hpp"
#include "data_structures/ArraySequence.h"
#include "compare.hpp"
#include <cassert>
#include <string>
#include "person.hpp"
#include "iostream"

void run_tests_for_int(ISorter<int>& sorter);
void run_tests_for_person(ISorter<person>& sorter);
void run_all_tests();

#endif // TESTS_HPP
