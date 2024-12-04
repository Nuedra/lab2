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

enum DataType {
    NORMAL_DATA = 1,
    SORTED_DATA = 2,
    REVERSE_SORTED_DATA = 3
};

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


void measure_and_save_sort_times(DataType data_type) {
    std::string filename;
    if (data_type == NORMAL_DATA) {
        filename = "../csv/sort_times.csv";
    }
    else if (data_type == SORTED_DATA) {
        filename = "../csv/sort_times_sorted.csv";
    }
    else if (data_type == REVERSE_SORTED_DATA) {
        filename = "../csv/sort_times_reverse_sorted.csv";
    }
    else {
        std::cerr << "Unknown data type!" << std::endl;
        return;
    }

    std::ofstream csv_file(filename);
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    csv_file << "Data Size,Bubble Sort ms,Quick Sort ms,Heap Sort ms,Insertion Sort ms" << std::endl;

    const int step = 250;
    for (int size = step; size <= step * 20; size += step) {
        std::string input_filename;

        // Генерация данных в зависимости от выбранного типа
        if (data_type == NORMAL_DATA) {
            generate_and_write_persons_to_file(size);
            input_filename = "../csv/data.csv";
        }
        else if (data_type == SORTED_DATA) {
            generate_and_write_sorted_persons_to_file(size);
            input_filename = "../csv/sorted.csv";
        }
        else {
            generate_and_write_reverse_sorted_persons_to_file(size);
            input_filename = "../csv/reverse_sorted.csv";
        }

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


void measure_and_save_sort_times_for_big(DataType data_type) {
    std::string filename;
    if (data_type == NORMAL_DATA) {
        filename = "../csv/sort_times_big_count.csv";
    }
    else if (data_type == SORTED_DATA) {
        filename = "../csv/sort_times_big_count_sorted.csv";
    }
    else if (data_type == REVERSE_SORTED_DATA) {
        filename = "../csv/sort_times_big_count_reverse_sorted.csv";
    }
    else {
        std::cerr << "Unknown data type!" << std::endl;
        return;
    }

    std::ofstream csv_file(filename);
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    csv_file << "Data Size,Quick Sort ms,Heap Sort ms" << std::endl;

    const int step = 1000000;
    for (int size = step; size <= step*10; size += step) {
        std::string input_filename;

        // Генерация данных в зависимости от выбранного типа
        if (data_type == NORMAL_DATA) {
            generate_and_write_persons_to_file(size);
            input_filename = "../csv/data.csv";
        }
        else if (data_type == SORTED_DATA) {
            generate_and_write_sorted_persons_to_file(size);
            input_filename = "../csv/sorted.csv";
        }
        else {
            generate_and_write_reverse_sorted_persons_to_file(size);
            input_filename = "../csv/reverse_sorted.csv";
        }

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
