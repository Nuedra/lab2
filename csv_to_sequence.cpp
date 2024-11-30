#include <string>
#include <fstream>
#include <sstream>
#include "SmrtPtr.hpp"
#include "data_structures/ArraySequence.h"
#include "person.hpp"

SmrtPtr<ArraySequence<Person>> read_csv(const std::string& filename) {
    SmrtPtr<ArraySequence<Person>> sequence = SmrtPtr<ArraySequence<Person>>(new ArraySequence<Person>());

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    // Пропустить заголовок
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string first_name, last_name, birth_year, height, weight, salary;

        // Разделение строки по запятым
        std::getline(stream, first_name, ',');
        std::getline(stream, last_name, ',');
        std::getline(stream, birth_year, ',');
        std::getline(stream, height, ',');
        std::getline(stream, weight, ',');
        std::getline(stream, salary, ',');

        // Создание объекта Person
        Person person;
        person.first_name = first_name;
        person.last_name = last_name;
        person.birth_year = std::stoi(birth_year);
        person.height = std::stof(height);
        person.weight = std::stof(weight);
        person.salary = std::stoi(salary);

        // Добавление в последовательность
        sequence->append(person);
    }

    file.close();
    return sequence;
}