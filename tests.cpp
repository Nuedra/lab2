#include "BubbleSorter.hpp"
#include "HeapSorter.hpp"
#include "InsertionSorter.hpp"
#include "QuickSorter.hpp"
#include "Person.hpp"
#include "tests.hpp"
#include <iostream>

// Тесты для всех сортировщиков
void run_all_tests() {
    // Тесты для int
    BubbleSorter<int> bubble_sorter_int;
    run_tests_for_int(bubble_sorter_int);

    HeapSorter<int> heap_sorter_int;
    run_tests_for_int(heap_sorter_int);

    InsertionSorter<int> insertion_sorter_int;
    run_tests_for_int(insertion_sorter_int);

    QuickSorter<int> quick_sorter_int;
    run_tests_for_int(quick_sorter_int);

    // Тесты для Person
    BubbleSorter<Person> bubble_sorter_person;
    run_tests_for_person(bubble_sorter_person);

    HeapSorter<Person> heap_sorter_person;
    run_tests_for_person(heap_sorter_person);

    InsertionSorter<Person> insertion_sorter_person;
    run_tests_for_person(insertion_sorter_person);

    QuickSorter<Person> quick_sorter_person;
    run_tests_for_person(quick_sorter_person);

    std::cout << "All tests are passed" << std::endl;
}