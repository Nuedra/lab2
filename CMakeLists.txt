cmake_minimum_required(VERSION 3.29)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp
        SmrtPtr.hpp
        Isorter.hpp
        QuickSorter.hpp
        compare.hpp
        person.hpp
        BubbleSorter.hpp
        InsertionSorter.hpp
        HeapSorter.hpp
        csv_actions.cpp
        csv_actions.hpp
        sort_timer.hpp
        tests.hpp
        tests.cpp
)
