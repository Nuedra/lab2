#include <iostream>
#include <string>
#include "BubbleSorter.hpp"
#include "SmrtPtr.hpp"
#include "data_structures/ArraySequence.h"
#include "QuickSorter.hpp"
#include "compare.hpp"
#include "InsertionSorter.hpp"
#include "person.hpp"
#include "HeapSorter.hpp"
#include "create_random.hpp"
#include "csv_to_sequence.hpp"
#include "sort_timer.hpp"
#include "tests.hpp"


int main() {
    generate_and_write_persons_to_file(1000);

    std::string input_filename = "../csv/test.csv";
    SmrtPtr<ArraySequence<Person>> sequence = read_csv(input_filename);

    // Bubble Sort
    long long bubble_time = measure_sort_time<BubbleSorter<Person>, Person>(sequence, &Person::salary,"../csv/bubble.csv");
    std::cout << "Bubble Sort took " << bubble_time << " ms.\n";

    // Quick Sort
    long long quick_time = measure_sort_time<QuickSorter<Person>, Person>(sequence, &Person::height,"../csv/quick.csv");
    std::cout << "Quick Sort took " << quick_time << " ms.\n";

    // Heap Sort
    long long heap_time = measure_sort_time<HeapSorter<Person>, Person>(sequence, &Person::height,"../csv/heap.csv");
    std::cout << "Heap Sort took " << heap_time << " ms.\n";

    //Insertion Sort
    long long insertion_time = measure_sort_time<InsertionSorter<Person>, Person>(sequence, &Person::height,"../csv/insert.csv");
    std::cout << "Insertion Sort took " << insertion_time << " ms.\n";

    run_all_tests();

    return 0;
}
