#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para sleep()
#include <string.h>

#define CONSUMER "gpio-monitor"
#define CHIPNAME "gpiochip0"

int main() {
    struct gpiod_chip *chip;
    struct gpiod_line *lines[4];
    int input_pins[] = {4, 17, 27, 22};
    int last_states[4] = { -1, -1, -1, -1 }; // Para detectar cambios
    size_t i;

    chip = gpiod_chip_open_by_name(CHIPNAME);
    if (!chip) {
        perror("Error abriendo gpiochip");
        return EXIT_FAILURE;
    }

    for (i = 0; i < 4; i++) {
        lines[i] = gpiod_chip_get_line(chip, input_pins[i]);
        if (!lines[i]) {
            fprintf(stderr, "Error obteniendo pin %d\n", input_pins[i]);
            gpiod_chip_close(chip);
            return EXIT_FAILURE;
        }
        if (gpiod_line_request_input(lines[i], CONSUMER) < 0) {
            fprintf(stderr, "Error configurando pin %d como entrada\n", input_pins[i]);
            gpiod_chip_close(chip);
            return EXIT_FAILURE;
        }
    }

    printf("Monitor de entradas iniciado...\n");

    while (1) {
        for (i = 0; i < 4; i++) {
            int value = gpiod_line_get_value(lines[i]);
            if (value < 0) {
                fprintf(stderr, "Error leyendo pin %d\n", input_pins[i]);
                continue;
            }

            // Solo reporta cambios (opcional, puedes quitar esta condición si quieres imprimir siempre)
            if (last_states[i] != value) {
                printf("Pin %d -> Estado: %d\n", input_pins[i], value);
                last_states[i] = value;
            }
        }

        usleep(100 * 1000); // Espera 100 ms entre lecturas
    }

    gpiod_chip_close(chip);
    return EXIT_SUCCESS;
}

