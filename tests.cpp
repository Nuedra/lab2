#include "BubbleSorter.hpp"
#include "HeapSorter.hpp"
#include "InsertionSorter.hpp"
#include "QuickSorter.hpp"
#include "person.hpp"
#include "tests.hpp"
#include <iostream>


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