#include "signal_sender.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Uso: %s <numero_de_pin> <valor (0 o 1)>\n", argv[0]);
        return 1;
    }

    int pin = atoi(argv[1]);
    int value = atoi(argv[2]);

    if (value != 0 && value != 1) {
        printf("Error: El valor debe ser 0 o 1\n");
        return 1;
    }

    int resultado = signal_sender(pin, value);
    if (resultado != 0) {
        printf("Error al configurar el pin %d\n", pin);
        return 1;
    }

    printf("Pin %d configurado a %d correctamente\n", pin, value);
    return 0;
}
