#include "sort_comparison.hpp"
#include <iostream>
#include <chrono>
#include "BubbleSorter.hpp"
#include "HeapSorter.hpp"
#include "InsertionSorter.hpp"
#include "QuickSorter.hpp"
#include "person.hpp"
#include <fstream>
#include <cstdio>
#include <string>

ArraySequence<Person> load_persons_from_csv(const std::string& filename) {
    ArraySequence<Person> persons;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return persons;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        Person person;
        char first_name[100], last_name[100];
        if (sscanf(line.c_str(), "%99[^,],%99[^,],%d,%f,%f,%d", first_name, last_name, &person.birth_year,
                   &person.height, &person.weight, &person.salary) == 6){
            person.first_name = first_name;
            person.last_name = last_name;
            persons.append(person);
            }
    }

    file.close();
    return persons;
}

void compare_sorting_algorithms(const ArraySequence<Person>& persons, int (*cmp)(const Person&, const Person&)) {
    if (persons.get_length() == 0) {
        std::cerr << "No data to sort." << std::endl;
        return;
    }

    // Создаем копии данных для каждого сортировщика
    ArraySequence<Person> persons_bubble = persons;
    ArraySequence<Person> persons_heap = persons;
    ArraySequence<Person> persons_insertion = persons;
    ArraySequence<Person> persons_quick = persons;

    // Сортировка методом пузырька
    BubbleSorter<Person> bubble_sorter;
    auto start = std::chrono::high_resolution_clock::now();
    bubble_sorter.Sort(SmrtPtr<ArraySequence<Person>>(new ArraySequence<Person>(persons_bubble)), cmp);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> bubble_sort_time = end - start;
    std::cout << "Bubble Sort time: " << bubble_sort_time.count() << " seconds" << std::endl;

    // Сортировка методом пирамидальной сортировки
    HeapSorter<Person> heap_sorter;
    start = std::chrono::high_resolution_clock::now();
    heap_sorter.Sort(SmrtPtr<ArraySequence<Person>>(new ArraySequence<Person>(persons_heap)), cmp);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> heap_sort_time = end - start;
    std::cout << "Heap Sort time: " << heap_sort_time.count() << " seconds" << std::endl;

    // Сортировка методом вставки
    InsertionSorter<Person> insertion_sorter;
    start = std::chrono::high_resolution_clock::now();
    insertion_sorter.Sort(SmrtPtr<ArraySequence<Person>>(new ArraySequence<Person>(persons_insertion)), cmp);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertion_sort_time = end - start;
    std::cout << "Insertion Sort time: " << insertion_sort_time.count() << " seconds" << std::endl;

    // Быстрая сортировка
    QuickSorter<Person> quick_sorter;
    start = std::chrono::high_resolution_clock::now();
    quick_sorter.Sort(SmrtPtr<ArraySequence<Person>>(new ArraySequence<Person>(persons_quick)), cmp);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> quick_sort_time = end - start;
    std::cout << "Quick Sort time: " << quick_sort_time.count() << " seconds" << std::endl;
}
