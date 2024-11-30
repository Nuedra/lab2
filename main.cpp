#include <iostream>
#include <string>
#include "BubbleSorter.hpp"
#include "SmrtPtr.hpp"
#include "data_structures/ArraySequence.h"
#include "QuickSorter.hpp"
#include "InsertionSorter.hpp"
#include "person.hpp"
#include "HeapSorter.hpp"
#include "create_random.hpp"
#include "csv_to_sequence.hpp"
#include "sort_timer.hpp"
#include "tests.hpp"


int main() {
    run_all_tests();
    measure_and_save_sort_times();
    measure_and_save_sort_times_for_big();

    return 0;
}
