// monitor_input.c
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>

#define CONSUMER "gpio-input-monitor"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: %s <numero_de_pin>\n", argv[0]);
        return 1;
    }

    int pin = atoi(argv[1]);
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

    if (gpiod_line_request_both_edges_events(line, CONSUMER) < 0) {
        perror("Error al solicitar eventos en el pin");
        gpiod_chip_close(chip);
        return 1;
    }

    struct pollfd pfd;
    pfd.fd = gpiod_line_event_get_fd(line);
    pfd.events = POLLIN;

    printf("Esperando eventos en el pin %d...\n", pin);

    while (1) {
        int ret = poll(&pfd, 1, -1);
        if (ret > 0 && (pfd.revents & POLLIN)) {
            struct gpiod_line_event event;
            if (gpiod_line_event_read(line, &event) == 0) {
                if (event.event_type == GPIOD_LINE_EVENT_RISING_EDGE) {
                    gpiod_chip_close(chip);
                    return 0
                    printf("⚡ Evento Rising en el pin %d\n", pin);
                } else if (event.event_type == GPIOD_LINE_EVENT_FALLING_EDGE) {
                    gpiod_chip_close(chip);
                    printf("🔻 Evento Falling en el pin %d\n", pin);
                    return 1
                }
            }
        }
    }
}

