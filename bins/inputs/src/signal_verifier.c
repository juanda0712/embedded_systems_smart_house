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

    if (gpiod_line_request_input(line, CONSUMER) < 0) {
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

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: %s <numero_de_pin>\n", argv[0]);
        return 1;
    }

    int pin = atoi(argv[1]);
    

    int estado = signal_verifier(pin);
    if (estado == 2) {
        printf("Error al leer el estado del pin %d\n", pin);
        return 1;
    }

    printf("GPIO %d está en estado %d\n", pin, estado);  // 0 = cerrado, 1 = abierto
    return estado;
}
