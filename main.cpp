#include <iostream>
#include <string>
#include "BubbleSorter.hpp"
#include "SmrtPtr.hpp"
#include "data_structures/ArraySequence.h"
#include "QuickSorter.hpp"
#include "InsertionSorter.hpp"
#include "person.hpp"
#include "HeapSorter.hpp"
#include "csv_actions.hpp"
#include "sort_timer.hpp"
#include "tests.hpp"
#include "compare.hpp"

int main() {
    // Генерация данных
    const int number_of_persons = 100;
    generate_and_write_persons_to_file(number_of_persons);

    // Чтение данных из файла
    auto persons = read_csv("../csv/test.csv");

    // Создание сортировщика
    QuickSorter<person> sorter;

    // Очистка цепочки компараторов
    ChainedComparator<person>::ClearComparators();

    // Добавление компараторов по ключам (в порядке приоритета: от низшего к высшему)
    ComparatorWrapper<person, int>::SetKey(&person::birth_year);
    ChainedComparator<person>::AddComparator(ComparatorWrapper<person, int>::Compare);

    ComparatorWrapper<person, int>::SetKey(&person::salary);
    ChainedComparator<person>::AddComparator(ComparatorWrapper<person, int>::Compare);

    ComparatorWrapper<person, std::string>::SetKey(&person::last_name);
    ChainedComparator<person>::AddComparator(ComparatorWrapper<person, std::string>::Compare);

    // Сортировка с использованием цепочки компараторов
    persons = sorter.Sort(persons, ChainedComparator<person>::Compare);

    // Запись отсортированных данных в CSV-файл
    write_csv("../csv/sorted_persons.csv", persons);

    // Выполнение тестов (если необходимо)
    // run_all_tests();
    // measure_and_save_sort_times();
    // measure_and_save_sort_times_for_big();

    return 0;
}
