cmake_minimum_required(VERSION 3.13)
project(signal_verifier C)

# Incluir directorios
include_directories(include)

# Buscar libgpiod con pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED libgpiod)

# Crear la biblioteca compartida de signal_verifier
add_library(signal_verifier_lib SHARED lib/signal_verifier_lib.c)
target_link_libraries(signal_verifier_lib ${GPIOD_LIBRARIES})

# Ejecutable principal
add_executable(signal_verifier src/signal_verifier.c)
target_link_libraries(signal_verifier signal_verifier_lib ${GPIOD_LIBRARIES})

# Salida en bin/
set_target_properties(signal_verifier PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Salida de la biblioteca compartida en lib/
set_target_properties(signal_verifier_lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)	
