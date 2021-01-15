#include <iostream>
#include <vector>
#include <fstream>

#include "yaml-cpp/yaml.h"

#include "src/integral.h"
#include "src/integral_functions.h"
#include "src/time_measurement.h"
#include "src/csv_writer.h"


int main(int argc, char * argv[]) {
    std::cout.precision(17);

    std::string config_filename = std::string(argv[1]);
    std::string log_filename = std::string(argv[2]);

    YAML::Node config = YAML::LoadFile(config_filename);
    CsvWriter csv_writer(log_filename);

    std::vector<std::string> log_columns = {"n_threads", "time"};
    csv_writer.add_line(log_columns);

    auto repeat = config["repeat"].as<int>();
    auto arg_func_name = config["function"].as<std::string>();
    auto arg_func = integral_func_map[arg_func_name];
    auto x_interval = config["x_interval"].as<std::pair<double, double>>();
    auto y_interval = config["y_interval"].as<std::pair<double, double>>();
    auto n_threads = config["n_threads"].as<std::vector<int>>();
    auto delta = config["delta"].as<double>();
    auto diff = config["diff"].as<double>();
    auto verbose = config["verbose"].as<bool>();

    std::cout << "function: " << arg_func_name << std::endl;
    std::cout << "x interval from: " << x_interval.first << " till: "<< x_interval.second <<std::endl;
    std::cout << "y interval from: " << y_interval.first << " till: "<< y_interval.second <<std::endl;
    std::cout << "max abs error: " << delta << " initial diff: " << diff << std::endl;
    std::cout << std::endl;

    for (auto n_tr: n_threads) {
        double mean_time = 0.0;

        for (int i = 0; i < repeat; ++i) {
            std::cout << "num of threads: " << n_tr << " attempt: " << i+1 << std::endl;
            auto start_time = get_current_time_fenced();

            auto res = calc_integral_parallel_with_precision(
                    arg_func,
                    x_interval.first, x_interval.second,
                    y_interval.first, y_interval.second,
                    diff, delta, n_tr, verbose
            );

            auto finish_time = get_current_time_fenced();
            auto total_time = finish_time - start_time;
            mean_time += to_sec(total_time);

            std::cout << "integral value: " << std::get<0>(res) << std::endl;
            std::cout << "abs error: " << std::get<1>(res) << " rel error: " << std::get<2>(res) << std::endl;
            std::cout << "num of iterations: " << std::get<3>(res) << std::endl;
            std::cout << "total time, s: " << to_sec(total_time) << std::endl;
            std::cout << std::endl;

            std::vector<std::string> log_values = {std::to_string(n_tr), std::to_string(to_sec(total_time))};
            csv_writer.add_line(log_values);
        }

        mean_time /= (repeat * n_threads.size());
        std::cout << "mean time per attempt, s: " << mean_time << std::endl;
        std::cout << std::endl;
    }

    csv_writer.close();

    return 0;
}
