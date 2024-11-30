#ifndef SORT_TIMER_HPP
#define SORT_TIMER_HPP

#include <chrono>
#include <string>
#include "data_structures/ArraySequence.h"
#include "InsertionSorter.hpp"

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

#endif // SORT_TIMER_HPP
