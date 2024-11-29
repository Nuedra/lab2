#ifndef CREATE_RANDOM_HPP
#define CREATE_RANDOM_HPP

#include <string>
#include <vector>
#include "person.hpp"

std::vector<std::string> load_names_from_file(const std::string& filename);

std::string generate_random_name(const std::vector<std::string>& names);

int generate_random_int(int min, int max);

float generate_random_float(float min, float max);

void generate_and_write_persons_to_file(int number_of_persons);

#endif // CREATE_RANDOM_HPP
