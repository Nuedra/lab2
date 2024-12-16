#ifndef SORT_TIMER_HPP
#define SORT_TIMER_HPP

#include <fstream>
#include <chrono>
#include <string>
#include "BubbleSorter.hpp"
#include "QuickSorter.hpp"
#include "HeapSorter.hpp"
#include "InsertionSorter.hpp"
#include "data_structures/ArraySequence.h"
#include "person.hpp"
#include "csv_actions.hpp"
#include "graphics.hpp"

enum DataType {
    NORMAL_DATA = 1,
    SORTED_DATA = 2,
    REVERSE_SORTED_DATA = 3
};

long measure_sort_time(ISorter<person>& sorter,
                       const ArraySequence<person>& sequence,
                       int (*cmp)(const person&, const person&),
                       ArraySequence<person>& sorted_sequence,
                       std::string name);

void measure_and_save_sort_times(DataType data_type);

void measure_and_save_sort_times_for_big();

#endif // SORT_TIMER_HPP
