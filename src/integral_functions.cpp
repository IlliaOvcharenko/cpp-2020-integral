#include "integral_functions.h"


double de_jong(double x1, double x2) {
    double res = 0;

    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            res += 1.0 / (5.0 * (i + 2.0) + j + 3.0 \
                + pow(x1 - 16.0 * j, 6) \
                + pow(x2 - 16.0 * i, 6));
        }
    }

    res += 0.002;
    res = pow(res, -1);
    return res;
}

double ackley(double x1, double x2) {
    double a = 20;
    double b = 0.2;
    double c = 2*M_PIl;

    double res = 0;
    res += -a * exp(-b * sqrt(1.0/2.0 * (pow(x1, 2) + pow(x2, 2))));
    res += -exp(1.0/2.0 * (cos(c * x1) + cos(c*x2)));
    res += a + exp(1);
    return res;
}

double shubert(double x1, double x2) {
    int m = 5;

    double first_sum = 0.0;
    for (int i = 1; i <= m; ++i) {
        first_sum += i * cos((i + 1) * x1 + 1);
    }

    double second_sum = 0.0;
    for (int i = 1; i <= m; ++i) {
        second_sum += i * cos((i + 1) * x2 + 1);
    }

    double res = -first_sum * second_sum;
    return res;
}

double langermann(double x1, double x2) {
    int m = 5;
    int a1[] = {1, 2, 1, 1, 5};
    int a2[] = {4, 5, 1, 2, 4};
    int c[] = {2, 1, 4, 7, 2};


    double res = 0.0;

    for (int i = 1; i <= m; ++i) {
        res += c[i-1] * exp(-1.0/M_PI * (pow((x1 - a1[i-1]), 2) + pow((x2 - a2[i-1]), 2))) \
                      * cos(M_PI * (pow((x1 - a1[i-1]), 2) + pow((x2 - a2[i-1]), 2)));
    }
    res = -res;
    return res;
}

std::map<std::string, integral_func> integral_func_map = {
        {"de_jong", de_jong},
        {"ackley", ackley},
        {"shubert", shubert},
        {"langermann", langermann},
};
