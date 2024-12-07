cmake_minimum_required(VERSION 3.29)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

# Поиск Boost с необходимыми компонентами
find_package(Boost REQUIRED COMPONENTS iostreams)

if(Boost_FOUND)
    message(STATUS "Boost найден!")
    message(STATUS "Boost Include Dirs: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost Libraries: ${Boost_LIBRARIES}")
else()
    message(FATAL_ERROR "Boost не найден!")
endif()

# Включение заголовочных файлов Boost
include_directories(${Boost_INCLUDE_DIRS})

# Добавление исполняемого файла
add_executable(lab2
        main.cpp
        Isorter.hpp
        Sorts/QuickSorter.hpp
        compare.hpp
        person.hpp
        Sorts/BubbleSorter.hpp
        Sorts/InsertionSorter.hpp
        Sorts/HeapSorter.hpp
        csv_actions.cpp
        csv_actions.hpp
        sort_timer.hpp
        tests.hpp
        graphics.cpp
        graphics.hpp
)

# Линковка с библиотеками Boost
target_link_libraries(lab2 ${Boost_LIBRARIES})
