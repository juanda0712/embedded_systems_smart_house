// src/signal_sender.c
#include "signal_sender.h"
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>

int output_pins[] = {5, 6, 13, 19, 26};
int output_count = sizeof(output_pins) / sizeof(int);

int pin_es_valido(int pin) {
    for (int i = 0; i < output_count; i++) {
        if (output_pins[i] == pin) {
            return 1;
        }
    }
    return 0;
}

int signal_sender(int pin, int value) {
    if (!pin_es_valido(pin)) {
        printf("Error: El pin %d no está permitido como salida\n", pin);
        return 1;
    }

    const char *chipname = "gpiochip0";
    struct gpiod_chip *chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        perror("Error al abrir el chip GPIO");
        return 1;
    }

    struct gpiod_line *line = gpiod_chip_get_line(chip, pin);
    if (!line) {
        perror("Error al obtener la línea GPIO");
        gpiod_chip_close(chip);
        return 1;
    }

    if (gpiod_line_request_output(line, CONSUMER, value) < 0) {
        perror("Error al solicitar control del pin");
        gpiod_chip_close(chip);
        return 1;
    }

    if (gpiod_line_set_value(line, value) < 0) {
        perror("Error al establecer valor del pin");
        gpiod_chip_close(chip);
        return 1;
    }

    printf("GPIO %d establecido a %d\n", pin, value);

    gpiod_chip_close(chip);
    return 0;
}
