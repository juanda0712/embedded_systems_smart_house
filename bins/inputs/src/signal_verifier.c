// monitor_input.c
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>

#define CONSUMER "gpio-input-monitor"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: %s <numero_de_pin>\n", argv[0]);
        return 2;
    }

    int pin = atoi(argv[1]);
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

    if (value == 1) {
        printf("⚡ Pin %d está en ALTO (HIGH)\n", pin);
        return 0;
    } else {
        printf("🔻 Pin %d está en BAJO (LOW)\n", pin);
        return 1;
    }
}

