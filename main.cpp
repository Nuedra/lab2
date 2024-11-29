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

int main() {

    generate_and_write_persons_to_file(10000);

    return 0;
}

