#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

struct Person {
    std::string first_name;
    std::string last_name;
    int birth_year{};
    float height{};
    float weight{};
    std::string city;
    std::string phone;
    int salary{};
};

#endif // PERSON_HPP

