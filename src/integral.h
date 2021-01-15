#ifndef CPP_2020_INTEGRAL_INTEGRAL_H
#define CPP_2020_INTEGRAL_INTEGRAL_H

#include <iostream>
#include <cmath>
#include <thread>
#include <vector>

void calc_integral(
        double (*func)(double, double),
        double x_from, double x_till, double dx,
        double y_from, double y_till, double dy,
        double& return_val
);

double calc_integral_parallel(
        double (*func)(double, double),
        double x_from, double x_till, double dx,
        double y_from, double y_till, double dy,
        double& return_val,
        int n_threads,
        double x_shift=0.0, double y_shift=0.0
);

//double calc_integral_with_precision(
//        double (*func)(double, double),
//        double x_from, double x_till,
//        double y_from, double y_till,
//        double delta,
//        double diff=0.1
//);


typedef std::tuple<double, double, double, int> calc_integral_result;
calc_integral_result calc_integral_parallel_with_precision(
        double (*func)(double, double),
        double x_from, double x_till,
        double y_from, double y_till,
        double init_diff,
        double abs_err_delta,
        int n_threads,
        bool verbose=false
);

//double calc_integral_parallel_with_precision(
//        double (*func)(double, double),
//        double x_from, double x_till,
//        double y_from, double y_till,
//        double delta,
//        int n_threads,
//        double diff=0.1
//);


#endif //CPP_2020_INTEGRAL_INTEGRAL_H
