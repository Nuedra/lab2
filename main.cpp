#include <iostream>
#include "QuickSorter.hpp"
#include "person.hpp"
#include "csv_actions.hpp"
#include "sort_timer.hpp"
#include "tests.hpp"
#include "compare.hpp"
#include "gnuplot-iostream.h"

void display_menu() {
    std::cout << "\nConsole Interface Menu:" << std::endl;
    std::cout << "1. Run sorting tests" << std::endl;
    std::cout << "2. Compare sorting time on normal data (salary) on random, sorted or reverse_sorted" << std::endl;
    std::cout << "3. Compare sorting time on large data (salary)" << std::endl;
    std::cout << "4. Sort by one attribute (salary)" << std::endl;
    std::cout << "5. Sort by two attributes (salary, last_name)" << std::endl;
    std::cout << "6. Sort by three attributes (salary, last_name, height)" << std::endl;
    std::cout << "7. Exit" << std::endl;
}

int get_valid_choice(int min, int max) {
    char input_str[100];
    int choice;

    while (true) {
        std::cout << "Select an action (" << min << "-" << max << "): ";
        std::cin.getline(input_str, 100);
        choice = atoi(input_str);

        if (choice >= min && choice <= max) {
            return choice;
        }
        std::cout << "Invalid choice. Please enter a number between " << min << " and " << max << "." << std::endl;
    }
}

int get_positive_integer(const std::string& prompt) {
    char input_str[100];
    int number;

    while (true) {
        std::cout << prompt;
        std::cin.getline(input_str, 100);
        number = atoi(input_str);
        if (number > 0) {
            return number;
        }
        std::cout << "Invalid number. Please enter a positive integer." << std::endl;
    }
}

void sort_and_save(const std::string& input_file, const std::string& output_file,
                   int (*comparator)(const person&, const person&)) {
    auto persons = read_csv(input_file);
    QuickSorter<person> sorter;
    sorter.Sort(persons, comparator);
    write_csv(output_file, persons);
}

void output_on_screen(std::string filename){
    std::string command = "open " + filename;
    system(command.c_str());
}

void console_interface() {
    std::string filename = "../csv/data.csv";
    while (true) {
        display_menu();
        int choice = get_valid_choice(1, 7);

        if (choice == 1) {
            run_all_tests();
        }
        else if (choice == 2) {
            std::cout << "Select data type:" << std::endl;
            std::cout << "1. Random" << std::endl;
            std::cout << "2. Sorted data" << std::endl;
            std::cout << "3. Reverse-sorted data" << std::endl;

            int data_choice = get_valid_choice(1, 3);
            DataType data_type = (data_choice == 1) ? NORMAL_DATA :
                                 (data_choice == 2) ? SORTED_DATA : REVERSE_SORTED_DATA;

            measure_and_save_sort_times(data_type);
        }
        else if (choice == 3) {
            measure_and_save_sort_times_for_big();
        }
        else if (choice == 4) {
            std::string output_file = "../csv/sorted_by_salary.csv";
            int number_of_persons = get_positive_integer("Enter the number of people to generate: ");
            generate_and_write_persons_to_file(number_of_persons);
            sort_and_save(filename, output_file, compare_person_salary);
            output_on_screen(output_file);
        }
        else if (choice == 5) {
            std::string output_file = "../csv/sorted_by_salary_lastname.csv";
            int number_of_persons = get_positive_integer("Enter the number of people to generate: ");
            generate_and_write_persons_to_file(number_of_persons);
            sort_and_save(filename, output_file, compare_person_salary_lastname);
            output_on_screen(output_file);
        }
        else if (choice == 6) {
            std::string output_file = "../csv/sorted_by_salary_lastname_height.csv";
            int number_of_persons = get_positive_integer("Enter the number of people to generate: ");
            generate_and_write_persons_to_file(number_of_persons);
            sort_and_save(filename, output_file, compare_person_salary_lastname_height);
            output_on_screen(output_file);
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
