cmake_minimum_required(VERSION 3.13)
project(signal_sender C)

# Incluir directorios
include_directories(include)

# Crear biblioteca compartida desde lib/
add_library(signal_sender_lib SHARED lib/signal_sender_lib.c)
target_link_libraries(signal_sender_lib gpiod)

# Ejecutable principal desde src/
add_executable(signal_sender src/signal_sender.c)
target_link_libraries(signal_sender signal_sender_lib)

# Salida en bin/
set_target_properties(signal_sender PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Salida de la biblioteca compartida en lib/
set_target_properties(signal_sender_lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
