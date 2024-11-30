#include <iostream>
#include <fstream>
#include "data_structures/ArraySequence.h"
#include <string>
#include <random>
#include "person.hpp"
#include "create_random.hpp"
#include "SmrtPtr.hpp"

std::vector<std::string> load_names_from_file(const std::string& filename) {
    std::vector<std::string> names;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return names;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            names.push_back(line);
        }
    }
    file.close();
    return names;
}

std::string generate_random_name(const std::vector<std::string>& names) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, names.size() - 1);
    return names[distr(gen)];
}

int generate_random_int(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

float generate_random_float(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distr(min, max);
    return distr(gen);
}

void write_csv(const std::string& filename, SmrtPtr<ArraySequence<Person>> persons) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Записываем заголовки
    file << "first_name,last_name,birth_year,height,weight,salary\n";

    // Записываем данные
    for (int i = 0; i < persons->get_length(); ++i) {
        const auto& person = persons->get(i);
        file << person.first_name << ","
             << person.last_name << ","
             << person.birth_year << ","
             << person.height << ","
             << person.weight << ","
             << person.salary << "\n";
    }

    file.close();
}

void generate_and_write_persons_to_file(int number_of_persons) {
    std::vector<std::string> first_names = load_names_from_file("../names/first_names.txt");
    std::vector<std::string> last_names = load_names_from_file("../names/last_names.txt");

    SmrtPtr<ArraySequence<Person>> persons = SmrtPtr<ArraySequence<Person>>(new ArraySequence<Person>());

    // Генерация данных
    for (int i = 0; i < number_of_persons; ++i) {
        Person person;
        person.first_name = generate_random_name(first_names);
        person.last_name = generate_random_name(last_names);
        person.birth_year = generate_random_int(1950, 2010);
        person.height = generate_random_float(150.0, 200.0);
        person.weight = generate_random_float(50.0, 100.0);
        person.salary = generate_random_int(30000, 150000);
        persons->append(person);
    }

    // Используем выделенную функцию write_csv
    write_csv("../csv/test.csv", persons);

    std::cout << "File test.csv created with " << number_of_persons << " Person entries." << std::endl;
}
