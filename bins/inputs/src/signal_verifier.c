#include "signal_verifier.h"
#include <stdio.h>
#include <stdlib.h>

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

