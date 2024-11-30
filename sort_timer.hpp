#ifndef SORT_TIMER_HPP
#define SORT_TIMER_HPP

#include <fstream>
#include <chrono>
#include <string>
#include "BubbleSorter.hpp"
#include "QuickSorter.hpp"
#include "HeapSorter.hpp"
#include "InsertionSorter.hpp"
#include "SmrtPtr.hpp"
#include "data_structures/ArraySequence.h"
#include "person.hpp"
#include "csv_actions.hpp"

template <typename Sorter, typename T, typename KeyType>
long long measure_sort_time(SmrtPtr<ArraySequence<T>> sequence,
                            KeyType T::*key,
                            SmrtPtr<ArraySequence<T>>& sorted_sequence) {

    SmrtPtr<ArraySequence<T>> sequence_copy = SmrtPtr<ArraySequence<T>>(new ArraySequence<T>(*sequence));

    ComparatorWrapper<T, KeyType>::SetKey(key);

    auto start_time = std::chrono::high_resolution_clock::now();

    Sorter sorter;
    sorted_sequence = sorter.Sort(sequence_copy, ComparatorWrapper<T, KeyType>::Compare);

    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    return duration;
}

inline void measure_and_save_sort_times() {
    std::ofstream csv_file("../csv/sort_times.csv");
    csv_file << "Data Size,Bubble Sort ms,Quick Sort ms,Heap Sort ms,Insertion Sort ms" << std::endl;

    const int step = 500;
    for (int size = step; size <= 5000; size += step) {
        generate_and_write_persons_to_file(size);
        std::string input_filename = "../csv/test.csv";
        SmrtPtr<ArraySequence<person>> sequence = read_csv(input_filename);

        SmrtPtr<ArraySequence<person>> sorted_sequence;
        long long bubble_time = measure_sort_time<BubbleSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);
        long long quick_time = measure_sort_time<QuickSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);
        long long heap_time = measure_sort_time<HeapSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);
        long long insertion_time = measure_sort_time<InsertionSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);

        csv_file << size << "," << bubble_time << "," << quick_time << "," << heap_time << "," << insertion_time << std::endl;

        write_csv("../csv/last_sorted.csv", sorted_sequence);
    }

    csv_file.close();
}

inline void measure_and_save_sort_times_for_big() {
    std::ofstream csv_file("../csv/sort_times_big_count.csv");
    csv_file << "Data Size,Quick Sort ms,Heap Sort ms" << std::endl;

    const int step = 250000;
    for (int size = step; size <= 10000000; size += step) {
        generate_and_write_persons_to_file(size);
        std::string input_filename = "../csv/test.csv";
        SmrtPtr<ArraySequence<person>> sequence = read_csv(input_filename);

        SmrtPtr<ArraySequence<person>> sorted_sequence;
        long long quick_time = measure_sort_time<QuickSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);
        long long heap_time = measure_sort_time<HeapSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);

        csv_file << size << "," << quick_time << "," << heap_time << std::endl;

        write_csv("../csv/last_sorted_big.csv", sorted_sequence);
    }

    csv_file.close();
}

#endif // SORT_TIMER_HPP
