#include <iostream>
#include "BubbleSorter.hpp"
#include "SmrtPtr.hpp"
#include "data_structures/ArraySequence.h"
#include "QuickSorter.hpp"
#include "compare.hpp"
#include "InsertionSorter.hpp"
#include "Person.hpp"
#include "HeapSorter.hpp"
#include "create_random.hpp"
#include "sort_comparison.hpp"

int compare_by_first_name(const Person& a, const Person& b) {
    return compare_by_key(a, b, &Person::first_name);
}

int compare_by_last_name(const Person& a, const Person& b) {
    return compare_by_key(a, b, &Person::last_name);
}

int compare_by_birth_year(const Person& a, const Person& b) {
    return compare_by_key(a, b, &Person::birth_year);
}

int compare_by_height(const Person& a, const Person& b) {
    return compare_by_key(a, b, &Person::height);
}

int compare_by_weight(const Person& a, const Person& b) {
    return compare_by_key(a, b, &Person::weight);
}

int compare_by_salary(const Person& a, const Person& b) {
    return compare_by_key(a, b, &Person::salary);
}

int main() {
    generate_and_write_persons_to_file(10000);

    ArraySequence<Person> persons = load_persons_from_csv("../test.csv");

    // Спрашиваем пользователя, по какому ключу он хочет сортировать
    std::cout << "Choose key for sorting:\n";
    std::cout << "1. First Name\n";
    std::cout << "2. Last Name\n";
    std::cout << "3. Birth Year\n";
    std::cout << "4. Height\n";
    std::cout << "5. Weight\n";
    std::cout << "6. Salary\n";
    int choice;
    std::cin >> choice;

    int (*cmp)(const Person&, const Person&) = nullptr;

    switch (choice) {
        case 1:
            cmp = compare_by_first_name;
        break;
        case 2:
            cmp = compare_by_last_name;
        break;
        case 3:
            cmp = compare_by_birth_year;
        break;
        case 4:
            cmp = compare_by_height;
        break;
        case 5:
            cmp = compare_by_weight;
        break;
        case 6:
            cmp = compare_by_salary;
        break;
        default:
            std::cerr << "Invalid choice." << std::endl;
        return 1;
    }

    compare_sorting_algorithms(persons, cmp);

    return 0;
}

