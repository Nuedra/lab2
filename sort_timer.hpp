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
#include "Person.hpp"
#include "create_random.hpp"
#include "csv_to_sequence.hpp"

template <typename Sorter, typename T, typename KeyType>
long long measure_sort_time(SmrtPtr<ArraySequence<T>> sequence,
                            KeyType T::*key,
                            const std::string& output_filename = "") {
    // Создание копии последовательности для сортировки
    SmrtPtr<ArraySequence<T>> sequence_copy = SmrtPtr<ArraySequence<T>>(new ArraySequence<T>(*sequence));

    // Установка ключа для сравнения
    ComparatorWrapper<T, KeyType>::SetKey(key);

    // Запуск таймера
    auto start_time = std::chrono::high_resolution_clock::now();

    // Выполнение сортировки
    Sorter sorter;
    auto sorted_sequence = sorter.Sort(sequence_copy, ComparatorWrapper<T, KeyType>::Compare);

    // Остановка таймера
    auto end_time = std::chrono::high_resolution_clock::now();

    // Вычисление времени сортировки
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // Сохранение отсортированных данных в файл, если задано имя файла
    if (!output_filename.empty()) {
        write_csv(output_filename, sorted_sequence);
    }

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
        SmrtPtr<ArraySequence<Person>> sequence = read_csv(input_filename);

        // Замеры времени для каждого типа сортировки
        long long bubble_time = measure_sort_time<BubbleSorter<Person>, Person, int>(sequence, &Person::salary);
        long long quick_time = measure_sort_time<QuickSorter<Person>, Person, int>(sequence, &Person::salary);
        long long heap_time = measure_sort_time<HeapSorter<Person>, Person, int>(sequence, &Person::salary);
        long long insertion_time = measure_sort_time<InsertionSorter<Person>, Person, int>(sequence, &Person::salary);

        // Записываем строку таблицы с результатами в CSV файл
        csv_file << size << "," << bubble_time << "," << quick_time << "," << heap_time << "," << insertion_time << std::endl;
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
        SmrtPtr<ArraySequence<Person>> sequence = read_csv(input_filename);

        // Замеры времени для каждого типа сортировки
        long long quick_time = measure_sort_time<QuickSorter<Person>, Person, int>(sequence, &Person::salary);
        long long heap_time = measure_sort_time<HeapSorter<Person>, Person, int>(sequence, &Person::salary);

        // Записываем строку таблицы с результатами в CSV файл
        csv_file << size << "," << quick_time << "," << heap_time << std::endl;
    }

    // Закрываем CSV файл
    csv_file.close();
}

#endif // SORT_TIMER_HPP
