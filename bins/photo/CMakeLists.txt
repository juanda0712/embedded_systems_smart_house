cmake_minimum_required(VERSION 3.13)
project(photo C)

# Incluir directorios
include_directories(include)

# Ejecutable principal
add_executable(photo src/photo.c)

# Salida en bin/
set_target_properties(photo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

