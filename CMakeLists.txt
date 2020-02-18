cmake_minimum_required(VERSION 3.0.0)
project(measure_time VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(measure_time measure_time.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
