#include "signal_verifier.h"
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>

int signal_verifier(int pin) {
    const char *chipname = "gpiochip0";

    struct gpiod_chip *chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        perror("Error al abrir el chip GPIO");
        return 2;
    }

    struct gpiod_line *line = gpiod_chip_get_line(chip, pin);
    if (!line) {
        perror("Error al obtener la línea GPIO");
        gpiod_chip_close(chip);
        return 2;
    }

    if (gpiod_line_request_input(line, "signal_verifier") < 0) {
        perror("Error al solicitar la línea como entrada");
        gpiod_chip_close(chip);
        return 2;
    }

    int value = gpiod_line_get_value(line);
    if (value < 0) {
        perror("Error al leer el valor del pin");
        gpiod_chip_close(chip);
        return 2;
    }

    gpiod_chip_close(chip);

    return value == 1 ? 0 : 1;
}

