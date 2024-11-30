#ifndef CREATE_RANDOM_HPP
#define CREATE_RANDOM_HPP

#include <string>
#include <vector>
#include "person.hpp"
#include "SmrtPtr.hpp"

std::vector<std::string> load_names_from_file(const std::string& filename);

std::string generate_random_name(const std::vector<std::string>& names);

int generate_random_int(int min, int max);

float generate_random_float(float min, float max);

void write_csv(const std::string& filename, SmrtPtr<ArraySequence<person>> persons);

void generate_and_write_persons_to_file(int number_of_persons);

SmrtPtr<ArraySequence<person>> read_csv(const std::string& filename);

#endif // CREATE_RANDOM_HPP
