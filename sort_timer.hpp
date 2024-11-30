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
    // Создание копии последовательности для сортировки
    SmrtPtr<ArraySequence<T>> sequence_copy = SmrtPtr<ArraySequence<T>>(new ArraySequence<T>(*sequence));

    // Установка ключа для сравнения
    ComparatorWrapper<T, KeyType>::SetKey(key);

    // Запуск таймера
    auto start_time = std::chrono::high_resolution_clock::now();

    // Выполнение сортировки
    Sorter sorter;
    sorted_sequence = sorter.Sort(sequence_copy, ComparatorWrapper<T, KeyType>::Compare);

    // Остановка таймера
    auto end_time = std::chrono::high_resolution_clock::now();

    // Вычисление времени сортировки
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // Возврат времени выполнения
    return duration;
}

inline void measure_and_save_sort_times() {
    // Создаем и открываем CSV файл для записи результатов
    std::ofstream csv_file("../csv/sort_times.csv");
    csv_file << "Data Size,Bubble Sort ms,Quick Sort ms,Heap Sort ms,Insertion Sort ms" << std::endl;

    // Принцип изменения объема данных, начиная с 100 до 10,000 с шагом 100
    const int step = 500;
    for (int size = step; size <= 1000; size += step) {
        // Генерация тестовых данных
        generate_and_write_persons_to_file(size);
        std::string input_filename = "../csv/test.csv";
        SmrtPtr<ArraySequence<person>> sequence = read_csv(input_filename);

        // Замеры времени для каждого типа сортировки
        SmrtPtr<ArraySequence<person>> sorted_sequence;
        long long bubble_time = measure_sort_time<BubbleSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);
        long long quick_time = measure_sort_time<QuickSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);
        long long heap_time = measure_sort_time<HeapSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);
        long long insertion_time = measure_sort_time<InsertionSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);

        // Записываем строку таблицы с результатами в CSV файл
        csv_file << size << "," << bubble_time << "," << quick_time << "," << heap_time << "," << insertion_time << std::endl;

        // Сохранение последней отсортированной последовательности в файл
        write_csv("../csv/last_sorted.csv", sorted_sequence);
    }

    // Закрываем CSV файл
    csv_file.close();
}

inline void measure_and_save_sort_times_for_big() {
    // Создаем и открываем CSV файл для записи результатов
    std::ofstream csv_file("../csv/sort_times_big_count.csv");
    csv_file << "Data Size,Quick Sort ms,Heap Sort ms" << std::endl;

    // Принцип изменения объема данных, начиная с 100 до 10,000 с шагом 100
    const int step = 1000;
    for (int size = step; size <= 50000; size += step) {
        // Генерация тестовых данных
        generate_and_write_persons_to_file(size);
        std::string input_filename = "../csv/test.csv";
        SmrtPtr<ArraySequence<person>> sequence = read_csv(input_filename);

        // Замеры времени для каждого типа сортировки и сохранение последней отсортированной последовательности в файл
        SmrtPtr<ArraySequence<person>> sorted_sequence;
        long long quick_time = measure_sort_time<QuickSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);
        long long heap_time = measure_sort_time<HeapSorter<person>, person, int>(sequence, &person::salary, sorted_sequence);

        // Записываем строку таблицы с результатами в CSV файл
        csv_file << size << "," << quick_time << "," << heap_time << std::endl;

        // Сохранение последней отсортированной последовательности в файл
        write_csv("../csv/last_sorted_big.csv", sorted_sequence);
    }

    // Закрываем CSV файл
    csv_file.close();
}

#endif // SORT_TIMER_HPP
