cmake_minimum_required(VERSION 3.13)
project(signal_sender C)

# Incluir directorios
include_directories(include)

# Ejecutable principal
add_executable(signal_sender src/signal_sender.c)

# Bibliotecas necesarias
target_link_libraries(signal_sender gpiod)

# Salida en bin/
set_target_properties(signal_sender PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

