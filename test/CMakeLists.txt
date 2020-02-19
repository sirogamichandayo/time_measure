add_executable(measure_test test.cpp)
# tell include directory
target_include_directories(measure_test
    PUBLIC ${PROJECT_SOURCE_DIR}/include)
find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
message(STATUS "${PythonLibs}")
message(STATUS "${PYTHON_INCLUDE_DIRS}")
# link
target_link_libraries(measure_test ${PYTHON_LIBRARIES})