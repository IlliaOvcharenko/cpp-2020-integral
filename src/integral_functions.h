#ifndef CPP_2020_INTEGRAL_INTEGRAL_FUNCTIONS_H
#define CPP_2020_INTEGRAL_INTEGRAL_FUNCTIONS_H

#include <cmath>
#include <map>
#include <string>



double de_jong(double x1, double x2);

double ackley(double x1, double x2);

double shubert(double x1, double x2);

double langermann(double x1, double x2);

typedef double (*integral_func)(double x1, double x2);
extern std::map<std::string, integral_func> integral_func_map;



#endif //CPP_2020_INTEGRAL_INTEGRAL_FUNCTIONS_H
