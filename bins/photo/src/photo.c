#include "photo.h"
#include <stdio.h>
#include <stdlib.h>

int photo() {
    const char *device = "/dev/video0";
    const char *output_path = "/usr/share/mi-servidor-flask/static/picture.jpg";
    const char *command_template = "fswebcam -d %s --jpeg 95 -r 640x480 %s";
    char command[256];

    snprintf(command, sizeof(command), command_template, device, output_path);
    printf("Ejecutando: %s\n", command);

    int ret = system(command);
    if (ret == -1) {
        perror("Error ejecutando fswebcam");
        return EXIT_FAILURE;
    }

    printf("Foto capturada en %s\n", output_path);
    return EXIT_SUCCESS;
}

int main() {
    printf("Iniciando la captura de foto...\n");

    int result = photo();
    if (result == EXIT_SUCCESS) {
        printf("Foto tomada con éxito.\n");
    } else {
        printf("Error al tomar la foto.\n");
    }

    return result;
}

