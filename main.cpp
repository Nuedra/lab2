#include <iostream>
#include <cstdlib>
#include "QuickSorter.hpp"
#include "person.hpp"
#include "csv_actions.hpp"
#include "sort_timer.hpp"
#include "tests.hpp"
#include "compare.hpp"
#include "gnuplot-iostream.h"

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

        char choice_str[100];
        int choice;

        while (true) {
            std::cout << "Select an action (1-7): ";
            std::cin.getline(choice_str, 100);
            choice = atoi(choice_str);

            if (choice >= 1 && choice <= 7) {
                break;
            } else {
                std::cout << "Invalid choice. Please enter a number between 1 and 7." << std::endl;
            }
        }

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
            int number_of_persons;
            char input_str[100];

            while (true) {
                std::cout << "Enter the number of people to generate: ";
                std::cin.getline(input_str, 100);
                number_of_persons = atoi(input_str);
                if (number_of_persons > 0) {
                    break;
                } else {
                    std::cout << "Invalid number. Please enter a positive integer." << std::endl;
                }
            }

            generate_and_write_persons_to_file(number_of_persons);

            auto persons = read_csv("../csv/test.csv");
            QuickSorter<person> sorter;
            sorter.Sort(persons, compare_person_salary);
            write_csv("../csv/sorted_by_salary.csv", persons);
        }
        else if (choice == 5) {
            int number_of_persons;
            char input_str[100];

            while (true) {
                std::cout << "Enter the number of people to generate: ";
                std::cin.getline(input_str, 100);
                number_of_persons = atoi(input_str);
                if (number_of_persons > 0) {
                    break;
                } else {
                    std::cout << "Invalid number. Please enter a positive integer." << std::endl;
                }
            }

            generate_and_write_persons_to_file(number_of_persons);

            auto persons = read_csv("../csv/test.csv");
            QuickSorter<person> sorter;
            sorter.Sort(persons, compare_person_salary_lastname);
            write_csv("../csv/sorted_by_salary_lastname.csv", persons);
        }
        else if (choice == 6) {
            int number_of_persons;
            char input_str[100];

            while (true) {
                std::cout << "Enter the number of people to generate: ";
                std::cin.getline(input_str, 100);
                number_of_persons = atoi(input_str);
                if (number_of_persons > 0) {
                    break;
                } else {
                    std::cout << "Invalid number. Please enter a positive integer." << std::endl;
                }
            }

            generate_and_write_persons_to_file(number_of_persons);

            auto persons = read_csv("../csv/test.csv");
            QuickSorter<person> sorter;
            sorter.Sort(persons, compare_person_salary_lastname_height);
            write_csv("../csv/sorted_by_salary_lastname_height.csv", persons);
        }
        else {
            break;
        }
    }
}

int main() {
    console_interface();
    return 0;
}
