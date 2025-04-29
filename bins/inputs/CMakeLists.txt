cmake_minimum_required(VERSION 3.13)
project(signal_verifier C)

# Incluir directorios
include_directories(include)

# Ejecutable principal
add_executable(signal_verifier src/signal_verifier.c)

# Bibliotecas necesarias
target_link_libraries(signal_verifier gpiod)

# Salida en bin/
set_target_properties(signal_verifier PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

