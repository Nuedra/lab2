#ifndef SORT_TIMER_HPP
#define SORT_TIMER_HPP

#include <fstream>
#include <chrono>
#include <string>
#include "BubbleSorter.hpp"
#include "QuickSorter.hpp"
#include "HeapSorter.hpp"
#include "InsertionSorter.hpp"
#include "data_structures/ArraySequence.h"
#include "person.hpp"
#include "csv_actions.hpp"

long long measure_sort_time(ISorter<person>& sorter,
                            const ArraySequence<person>& sequence,
                            int (*cmp)(const person&, const person&),
                            ArraySequence<person>& sorted_sequence) {

    ArraySequence<person> sequence_copy(sequence);

    auto start_time = std::chrono::high_resolution_clock::now();

    sorter.Sort(sequence_copy, cmp);

    auto end_time = std::chrono::high_resolution_clock::now();

    sorted_sequence = sequence_copy;

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    return duration;
}


void measure_and_save_sort_times() {
    std::ofstream csv_file("../csv/sort_times.csv");
    csv_file << "Data Size,Bubble Sort ms,Quick Sort ms,Heap Sort ms,Insertion Sort ms" << std::endl;

    const int step = 500;
    for (int size = step; size <= 5000; size += step) {
        generate_and_write_persons_to_file(size);
        std::string input_filename = "../csv/test.csv";
        ArraySequence<person> sequence = read_csv(input_filename);

        ArraySequence<person> sorted_sequence;

        BubbleSorter<person> bubble_sorter;
        QuickSorter<person> quick_sorter;
        HeapSorter<person> heap_sorter;
        InsertionSorter<person> insertion_sorter;

        long long bubble_time = measure_sort_time(bubble_sorter, sequence, compare_person_salary, sorted_sequence);
        long long quick_time = measure_sort_time(quick_sorter, sequence, compare_person_salary, sorted_sequence);
        long long heap_time = measure_sort_time(heap_sorter, sequence, compare_person_salary, sorted_sequence);
        long long insertion_time = measure_sort_time(insertion_sorter, sequence, compare_person_salary, sorted_sequence);

        csv_file << size << "," << bubble_time << "," << quick_time << "," << heap_time << "," << insertion_time << std::endl;

    }

    csv_file.close();
}

void measure_and_save_sort_times_for_big() {
    std::ofstream csv_file("../csv/sort_times_big_count.csv");
    csv_file << "Data Size,Quick Sort ms,Heap Sort ms" << std::endl;

    const int step = 100000;
    for (int size = step; size <= 1000000; size += step) {
        generate_and_write_persons_to_file(size);
        std::string input_filename = "../csv/test.csv";
        ArraySequence<person> sequence = read_csv(input_filename);

        ArraySequence<person> sorted_sequence;

        QuickSorter<person> quick_sorter;
        HeapSorter<person> heap_sorter;

        long long quick_time = measure_sort_time(quick_sorter, sequence, compare_person_salary, sorted_sequence);
        long long heap_time = measure_sort_time(heap_sorter, sequence, compare_person_salary, sorted_sequence);

        csv_file << size << "," << quick_time << "," << heap_time << std::endl;

    }

    csv_file.close();
}

#endif // SORT_TIMER_HPP
