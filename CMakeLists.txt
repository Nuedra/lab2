cmake_minimum_required(VERSION 3.29)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp
        SmrtPtr.hpp
        Isorter.hpp
        QuickSorter.hpp
        compare.hpp
        Person.hpp
        tests.cpp
        BubbleSorter.hpp
        InsertionSorter.hpp
        HeapSorter.hpp
        create_random.cpp
        create_random.hpp)
