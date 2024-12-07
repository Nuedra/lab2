#ifndef TESTS_HPP
#define TESTS_HPP

#include "BubbleSorter.hpp"
#include "data_structures/ArraySequence.h"
#include "compare.hpp"
#include <cassert>
#include <string>
#include "person.hpp"
#include "iostream"

void run_tests_for_int(ISorter<int>& sorter) {
    ArraySequence<int> empty;
    sorter.Sort(empty, compare_default<int>);
    assert(empty.get_length() == 0);

    ArraySequence<int> sorted;
    sorted.append(1);
    sorted.append(2);
    sorted.append(3);
    sorted.append(4);
    sorted.append(5);
    sorter.Sort(sorted, compare_default<int>);
    for (int i = 0; i < sorted.get_length(); ++i) {
        assert(sorted.get(i) == (i + 1));
    }

    ArraySequence<int> reverse_sorted;
    reverse_sorted.append(5);
    reverse_sorted.append(4);
    reverse_sorted.append(3);
    reverse_sorted.append(2);
    reverse_sorted.append(1);
    sorter.Sort(reverse_sorted, compare_default<int>);
    for (int i = 0; i < reverse_sorted.get_length(); ++i) {
        assert(reverse_sorted.get(i) == (i + 1));
    }

    ArraySequence<int> duplicates;
    duplicates.append(4);
    duplicates.append(2);
    duplicates.append(2);
    duplicates.append(8);
    duplicates.append(3);
    duplicates.append(3);
    duplicates.append(1);
    sorter.Sort(duplicates, compare_default<int>);
    ArraySequence<int> expected_duplicates;
    expected_duplicates.append(1);
    expected_duplicates.append(2);
    expected_duplicates.append(2);
    expected_duplicates.append(3);
    expected_duplicates.append(3);
    expected_duplicates.append(4);
    expected_duplicates.append(8);
    for (int i = 0; i < duplicates.get_length(); ++i) {
        assert(duplicates.get(i) == expected_duplicates.get(i));
    }

    ArraySequence<int> single;
    single.append(42);
    sorter.Sort(single, compare_default<int>);
    assert(single.get_length() == 1);
    assert(single.get(0) == 42);

    ArraySequence<int> empty_array;
    sorter.Sort(empty_array, compare_default<int>);
    assert(empty_array.get_length() == 0);

    ArraySequence<int> single_element;
    single_element.append(5);
    sorter.Sort(single_element, compare_default<int>);
    assert(single_element.get_length() == 1);
    assert(single_element.get(0) == 5);

    ArraySequence<int> two_sorted;
    two_sorted.append(3);
    two_sorted.append(4);
    sorter.Sort(two_sorted, compare_default<int>);
    assert(two_sorted.get_length() == 2);
    assert(two_sorted.get(0) == 3);
    assert(two_sorted.get(1) == 4);

    ArraySequence<int> two_reverse_sorted;
    two_reverse_sorted.append(4);
    two_reverse_sorted.append(3);
    sorter.Sort(two_reverse_sorted, compare_default<int>);
    assert(two_reverse_sorted.get_length() == 2);
    assert(two_reverse_sorted.get(0) == 3);
    assert(two_reverse_sorted.get(1) == 4);
}

void run_tests_for_person(ISorter<person>& sorter) {
    ArraySequence<person> empty;
    sorter.Sort(empty, compare_person_salary);
    assert(empty.get_length() == 0);
    // Протестировать разные компораторы
    ArraySequence<person> persons;
    persons.append({"John", "Doe", 1985, 180.0f, 75.0f, 4000});
    persons.append({"Jane", "Smith", 1990, 165.0f, 60.0f, 3000});
    persons.append({"Alice", "Johnson", 1988, 170.0f, 65.0f, 5000});
    persons.append({"Bob", "Brown", 1982, 175.0f, 80.0f, 3500});
    sorter.Sort(persons, compare_person_salary);
    assert(persons.get(0).salary == 3000);
    assert(persons.get(1).salary == 3500);
    assert(persons.get(2).salary == 4000);
    assert(persons.get(3).salary == 5000);

}

void run_all_tests() {
    BubbleSorter<int> bubble_sorter_int;
    run_tests_for_int(bubble_sorter_int);

    HeapSorter<int> heap_sorter_int;
    run_tests_for_int(heap_sorter_int);

    InsertionSorter<int> insertion_sorter_int;
    run_tests_for_int(insertion_sorter_int);

    QuickSorter<int> quick_sorter_int;
    run_tests_for_int(quick_sorter_int);

    BubbleSorter<person> bubble_sorter_person;
    run_tests_for_person(bubble_sorter_person);

    HeapSorter<person> heap_sorter_person;
    run_tests_for_person(heap_sorter_person);

    InsertionSorter<person> insertion_sorter_person;
    run_tests_for_person(insertion_sorter_person);

    QuickSorter<person> quick_sorter_person;
    run_tests_for_person(quick_sorter_person);

    std::cout << "All tests are passed" << std::endl;
}

#endif // TESTS_HPP
