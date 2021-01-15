#include "integral.h"



void calc_integral(
        double (*func)(double, double),
        double x_from, double x_till, double dx,
        double y_from, double y_till, double dy,
        double& return_val
) {

    double val = 0.0;

    int x_n = ceil((x_till - x_from) / dx);
    int y_n = ceil((y_till - y_from) / dx);

    for (int i = 0; i < x_n; ++i) {
        for (int j = 0; j < y_n; ++j) {
            val += func(x_from + (i * dx), y_from + (j * dy)) * dx * dy;
        }
    }

    return_val = val;
}


double calc_integral_parallel(
        double (*func)(double, double),
        double x_from, double x_till, double dx,
        double y_from, double y_till, double dy,
        double& return_val,
        int n_threads,
        double x_shift, double y_shift
) {
    std::vector<std::thread> thread_list;
    std::vector<double> thread_results(n_threads, 0.0);

    double thread_step = (x_till - x_from) / n_threads;
    for (int i = 0; i < n_threads; ++i) {
        double thread_x_from = x_from + (i * thread_step);
        double thread_x_till = x_from + ((i+1) * thread_step);
//        std::cout << "thread: " << i << " from: " << thread_x_from << " till: " << thread_x_till << std::endl;
        thread_list.push_back(std::thread(
                calc_integral,
                func,
                thread_x_from + x_shift, thread_x_till, dx,
                y_from + y_shift, y_till, dy,
                std::ref(thread_results[i])
        ));
    }

    for (auto& t: thread_list) {
        t.join();
    }

    double val = 0.0;
    for (auto res: thread_results) {
        val += res;
    }

    return_val = val;
}


//double calc_integral_with_precision(
//    double (*func)(double, double),
//    double x_from, double x_till,
//    double y_from, double y_till,
//    double delta,
//    double diff
//) {
//    double integral_val;
//    calc_integral(func, x_from, x_till, diff, y_from, y_till, diff, integral_val);
//
//    double shift = diff / 2.0;
//    int iter_count = 1.0;
//
//    std::cout << "iter: " << iter_count << " value: " << integral_val << std::endl;
//    while (true) {
//        iter_count++;
//
//        double tmp_integral_val = integral_val / 4.0;
//
//        double tmp = 0.0;
//        calc_integral(
//                func,
//                x_from+shift, x_till, diff,
//                y_from, y_till, diff,
//                tmp
//        );
//        tmp_integral_val += tmp / 4.0;
//
//        calc_integral(
//                func,
//                x_from, x_till, diff,
//                y_from+shift, y_till, diff,
//                tmp
//        );
//        tmp_integral_val += tmp / 4.0;
//
//        calc_integral(
//                func,
//                x_from+shift, x_till, diff,
//                y_from+shift, y_till, diff,
//                tmp
//        );
//        tmp_integral_val += tmp / 4.0;
//
//        double step_err = fabs(tmp_integral_val - integral_val);
//        std::cout << "iter: " << iter_count << " value: " << tmp_integral_val << " shift: " << shift \
//                  << " error: " <<  step_err << " delta: " << delta \
//                  << " is greater: "<< (step_err <= delta) << std::endl;
//
//        if (step_err <= delta) {
//            return tmp_integral_val;
//        } else {
//            integral_val = tmp_integral_val;
//            shift /= 2;
//            diff /= 2;
//        }
//    }
//}

calc_integral_result calc_integral_parallel_with_precision(
        double (*func)(double, double),
        double x_from, double x_till,
        double y_from, double y_till,
        double init_diff,
        double abs_err_delta,
        int n_threads,
        bool verbose
) {
    double integral_val;
    calc_integral_parallel(func, x_from, x_till, init_diff, y_from, y_till, init_diff, integral_val, n_threads);

    double shift = init_diff / 2.0;
    int iter_count = 1.0;

    if (verbose) {
        std::cout << "iter: " << iter_count << " value: " << integral_val << std::endl;
    }

    while (true) {
        iter_count++;

        double tmp_integral_val = integral_val / 4.0;

        double tmp = 0.0;
        calc_integral_parallel(
                func,
                x_from, x_till, init_diff,
                y_from, y_till, init_diff,
                tmp,
                n_threads,
                shift, 0.0
        );
        tmp_integral_val += tmp / 4.0;

        calc_integral_parallel(
                func,
                x_from, x_till, init_diff,
                y_from, y_till, init_diff,
                tmp,
                n_threads,
                0.0, shift
        );
        tmp_integral_val += tmp / 4.0;

        calc_integral_parallel(
                func,
                x_from, x_till, init_diff,
                y_from, y_till, init_diff,
                tmp,
                n_threads,
                shift, shift
        );
        tmp_integral_val += tmp / 4.0;

        double abs_err = fabs(tmp_integral_val - integral_val);
        double rel_err = abs_err / tmp_integral_val;
        if (verbose) {
            std::cout << "iter: " << iter_count << " value: " << tmp_integral_val << " shift: " << shift \
                      << " rel err: " << rel_err << " abs err: " << abs_err << " abs err delta: " << abs_err_delta \
                      << std::endl;
        }

        if (abs_err <= abs_err_delta) {
            return calc_integral_result(tmp_integral_val, abs_err, rel_err, iter_count);
        } else {
            integral_val = tmp_integral_val;
            shift /= 2;
            init_diff /= 2;
        }
    }
}


