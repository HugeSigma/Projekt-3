cmake_minimum_required(VERSION 3.4...3.18)
project(cmake_example)

add_subdirectory(pybind11)
add_subdirectory(matplotplusplus)
add_subdirectory(AudioFile)
#add_subdirectory(opencv)

pybind11_add_module(cmake_example src/main.cpp)


target_link_libraries(cmake_example PUBLIC matplot)
target_link_libraries(cmake_example PUBLIC AudioFile)
#target_link_libraries(cmake_example PUBLIC opencv2)
# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(cmake_example
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
