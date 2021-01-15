cmake_minimum_required(VERSION 3.17)
project(cpp_2020_integral)

set(CMAKE_CXX_STANDARD 17)



add_subdirectory(libs/yaml-cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(
        calc_integral
        calc_integral.cpp
        src/integral_functions.cpp
        src/time_measurement.cpp
        src/integral.cpp
        src/csv_writer.cpp
)
target_link_libraries(calc_integral PRIVATE Threads::Threads)
target_link_libraries(calc_integral PRIVATE yaml-cpp::yaml-cpp)
