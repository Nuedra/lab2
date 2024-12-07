#include "graphics.hpp"
#include "gnuplot-iostream.h"
#include <vector>
#include <fstream>
#include <sstream>

void plot_sort_times(const std::string& csv_filename, const std::string& png_filename) {
    std::ifstream csv_file(csv_filename);
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open CSV file: " << csv_filename << std::endl;
        return;
    }

    std::string line;
    std::getline(csv_file, line);

    std::vector<std::string> headers;
    std::istringstream header_ss(line);
    std::string header_token;

    while (std::getline(header_ss, header_token, ',')) {
        headers.push_back(header_token);
    }

    if (headers.size() < 2) {
        std::cerr << "CSV file must have at least 'Data Size' and one sorting algorithm column." << std::endl;
        return;
    }

    if (headers[0] != "Data Size") {
        std::cerr << "First column must be 'Data Size'." << std::endl;
        return;
    }

    std::vector<int> data_sizes;
    std::vector<std::vector<long long>> sort_times(headers.size() - 1); // Количество сортировок

    while (std::getline(csv_file, line)) {
        std::istringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int data_size = std::stoi(token);
        data_sizes.push_back(data_size);

        for (size_t i = 0; i < sort_times.size(); ++i) {
            if (!std::getline(ss, token, ',')) {
                std::cerr << "Data row has missing columns." << std::endl;
                return;
            }
            sort_times[i].push_back(std::stoll(token));
        }
    }

    csv_file.close();

    Gnuplot gp;

    gp << "set terminal png size 800,600 enhanced font 'Arial,10'\n";
    gp << "set output '" << png_filename << "'\n";
    gp << "set title 'Sorting Time Comparison'\n";
    gp << "set xlabel 'Data Size'\n";
    gp << "set ylabel 'Time (ms)'\n";
    gp << "set grid\n";
    gp << "set key left top\n";

    // Формируем команду plot
    gp << "plot ";
    for (size_t i = 0; i < sort_times.size(); ++i) {
        if (i > 0) gp << ", ";
        gp << "'-' with linespoints title '" << headers[i + 1] << "'";
    }
    gp << "\n";

    // Отправляем данные
    for (size_t i = 0; i < sort_times.size(); ++i) {
        gp.send1d(boost::make_tuple(data_sizes, sort_times[i]));
    }

    std::string command1 = "open " + csv_filename;
    system(command1.c_str());

    std::string command2 = "open " + png_filename;
    system(command2.c_str());
}
