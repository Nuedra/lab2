#ifndef TESTS_HPP
#define TESTS_HPP

#include "BubbleSorter.hpp"
#include "data_structures/ArraySequence.h"
#include "compare.hpp"
#include <cassert>
#include <string>
#include "person.hpp"

// Универсальная функция тестирования для int
template<typename Sorter>
void run_tests_for_int(Sorter& sorter) {
    // Test 1: Empty array
    auto empty = SmrtPtr<ArraySequence<int>>(new ArraySequence<int>());
    sorter.Sort(empty, compare_default<int>);
    assert(empty->get_length() == 0);

    // Test 2: Already sorted array
    auto sorted = SmrtPtr<ArraySequence<int>>(new ArraySequence<int>());
    sorted->append(1);
    sorted->append(2);
    sorted->append(3);
    sorted->append(4);
    sorted->append(5);
    sorter.Sort(sorted, compare_default<int>);
    for (int i = 0; i < sorted->get_length(); ++i) {
        assert(sorted->get(i) == (i + 1));
    }

    // Test 3: Reverse sorted array
    auto reverse_sorted = SmrtPtr<ArraySequence<int>>(new ArraySequence<int>());
    reverse_sorted->append(5);
    reverse_sorted->append(4);
    reverse_sorted->append(3);
    reverse_sorted->append(2);
    reverse_sorted->append(1);
    sorter.Sort(reverse_sorted, compare_default<int>);
    for (int i = 0; i < reverse_sorted->get_length(); ++i) {
        assert(reverse_sorted->get(i) == (i + 1));
    }

    // Test 4: Array with duplicates
    auto duplicates = SmrtPtr<ArraySequence<int>>(new ArraySequence<int>());
    duplicates->append(4);
    duplicates->append(2);
    duplicates->append(2);
    duplicates->append(8);
    duplicates->append(3);
    duplicates->append(3);
    duplicates->append(1);
    sorter.Sort(duplicates, compare_default<int>);
    auto expected_duplicates = SmrtPtr<ArraySequence<int>>(new ArraySequence<int>());
    expected_duplicates->append(1);
    expected_duplicates->append(2);
    expected_duplicates->append(2);
    expected_duplicates->append(3);
    expected_duplicates->append(3);
    expected_duplicates->append(4);
    expected_duplicates->append(8);
    for (int i = 0; i < duplicates->get_length(); ++i) {
        assert(duplicates->get(i) == expected_duplicates->get(i));
    }

    // Test 5: Single element array
    auto single = SmrtPtr<ArraySequence<int>>(new ArraySequence<int>());
    single->append(42);
    sorter.Sort(single, compare_default<int>);
    assert(single->get_length() == 1);
    assert(single->get(0) == 42);
}

// Универсальная функция тестирования для person
template<typename Sorter>
void run_tests_for_person(Sorter& sorter) {
    ComparatorWrapper<person, int>::SetKey(&person::salary);

    // Test 1: Empty array
    auto empty = SmrtPtr<ArraySequence<person>>(new ArraySequence<person>());
    sorter.Sort(empty, ComparatorWrapper<person, int>::Compare);
    assert(empty->get_length() == 0);

    // Test 2: Array of Persons sorted by salary
    auto persons = SmrtPtr<ArraySequence<person>>(new ArraySequence<person>());
    persons->append({"John", "Doe", 1985, 180.0f, 75.0f, 4000});
    persons->append({"Jane", "Smith", 1990, 165.0f, 60.0f, 3000});
    persons->append({"Alice", "Johnson", 1988, 170.0f, 65.0f, 5000});
    persons->append({"Bob", "Brown", 1982, 175.0f, 80.0f, 3500});
    sorter.Sort(persons, ComparatorWrapper<person, int>::Compare);
    assert(persons->get(0).salary == 3000);
    assert(persons->get(1).salary == 3500);
    assert(persons->get(2).salary == 4000);
    assert(persons->get(3).salary == 5000);
}

void run_all_tests();

#endif // TESTS_HPP
