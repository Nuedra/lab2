#include <iostream>
#include <string>
#include "SmrtPtr.hpp"
#include "QuickSorter.hpp"
#include "person.hpp"
#include "csv_actions.hpp"
#include "sort_timer.hpp"
#include "tests.hpp"
#include "compare.hpp"
#include <fstream>

void console_interface() {
    while (true) {
        std::cout << "\nConsole Interface Menu:" << std::endl;
        std::cout << "1. Run sorting tests" << std::endl;
        std::cout << "2. Compare sorting time on normal data" << std::endl;
        std::cout << "3. Compare sorting time on large data" << std::endl;
        std::cout << "4. Sort by one attribute (salary)" << std::endl;
        std::cout << "5. Sort by two attributes (salary, last_name)" << std::endl;
        std::cout << "6. Sort by three attributes (salary, last_name, height)" << std::endl;
        std::cout << "7. Exit" << std::endl;

        int choice;
        std::cout << "Select an action (1-7): ";
        std::cin >> choice;

        if (choice == 1) {
            run_all_tests();
        }
        else if (choice == 2) {
            measure_and_save_sort_times();
        }
        else if (choice == 3) {
            measure_and_save_sort_times_for_big();
        }
        else if (choice == 4) {
            auto persons = read_csv("../csv/test.csv");
            QuickSorter<person> sorter;
            ChainedComparator<person>::ClearComparators();
            ComparatorWrapper<person, int>::SetKey(&person::salary);
            ChainedComparator<person>::AddComparator(ComparatorWrapper<person, int>::Compare);
            persons = sorter.Sort(persons, ChainedComparator<person>::Compare);
            write_csv("../csv/sorted_by_salary.csv", persons); // Немедленно записываем файл
        }
        else if (choice == 5) {
            auto persons = read_csv("../csv/test.csv");
            QuickSorter<person> sorter;
            ChainedComparator<person>::ClearComparators();
            ComparatorWrapper<person, int>::SetKey(&person::salary);
            ChainedComparator<person>::AddComparator(ComparatorWrapper<person, int>::Compare);
            ComparatorWrapper<person, std::string>::SetKey(&person::last_name);
            ChainedComparator<person>::AddComparator(ComparatorWrapper<person, std::string>::Compare);
            persons = sorter.Sort(persons, ChainedComparator<person>::Compare);
            write_csv("../csv/sorted_by_salary_lastname.csv", persons); // Немедленно записываем файл
        }
        else if (choice == 6) {
            auto persons = read_csv("../csv/test.csv");
            QuickSorter<person> sorter;
            ChainedComparator<person>::ClearComparators();
            ComparatorWrapper<person, int>::SetKey(&person::salary);
            ChainedComparator<person>::AddComparator(ComparatorWrapper<person, int>::Compare);
            ComparatorWrapper<person, std::string>::SetKey(&person::last_name);
            ChainedComparator<person>::AddComparator(ComparatorWrapper<person, std::string>::Compare);
            ComparatorWrapper<person, float>::SetKey(&person::height);
            ChainedComparator<person>::AddComparator(ComparatorWrapper<person, float>::Compare);
            persons = sorter.Sort(persons, ChainedComparator<person>::Compare);
            write_csv("../csv/sorted_by_salary_lastname_height.csv", persons); // Немедленно записываем файл
        }
        else if (choice == 7) {
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

int main() {
    int number_of_persons;
    std::cout << "Enter the number of people to generate: ";
    std::cin >> number_of_persons;
    generate_and_write_persons_to_file(number_of_persons); // Генерация данных сразу записывается в файл
    console_interface(); // Запуск консольного интерфейса
    return 0;
}
