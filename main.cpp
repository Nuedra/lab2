#include <iostream>
#include "SmrtPtr.hpp"
#include "data_structures/ArraySequence.h"
#include "QuickSorter.hpp"

struct Person {
    std::string first_name;
    std::string last_name;
    int birth_year{};
    float height{};
    float weight{};

    std::string city;
    std::string phone;
    int salary{};
};

template<typename T, typename Key>
int CompareByKey(const T& a, const T& b, Key T::*key) {
    if (a.*key < b.*key) {
        return -1;
    }
    if (a.*key > b.*key) {
        return 1;
    }
    return 0;
}

template<typename T>
int CompareDefault(const T& a, const T& b) {
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}


int main() {
    auto* seq_empty = new ArraySequence<Person>();
    seq_empty->append({"Alice", "Smith", 1995, 170.2, 65.0, "New York", "123-456-7890", 50000});
    seq_empty->append({"Bob", "Johnson", 1987, 180.3, 85.0, "Los Angeles", "234-567-8901", 70000});
    seq_empty->append({"Charlie", "Brown", 2000, 160.5, 50.0, "Chicago", "345-678-9012", 45000});

    SmrtPtr<ArraySequence<Person>> seq(seq_empty);
    QuickSorter<Person> quick_sorter;

    // Сортировка по зарплате
    quick_sorter.Sort(seq, [](const Person& a, const Person& b) {
       return CompareByKey(a, b, &Person::salary);
    });

    std::cout << "Sorted by salary:" << std::endl;
    for (int i = 0; i < seq->get_length(); ++i) {
        std::cout << seq->get(i).first_name << " (" << seq->get(i).salary << ")" << std::endl;
    }

    return 0;
}

