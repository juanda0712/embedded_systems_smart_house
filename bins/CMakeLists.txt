cmake_minimum_required(VERSION 3.13)
project(control_casa C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(inputs)
add_subdirectory(outputs)
add_subdirectory(photo)

