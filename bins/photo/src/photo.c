#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *output_file = "/tmp/foto.jpg";  // Foto guardada en tmp
    const char *device = "/dev/video0";          // Dispositivo cámara
    const char *command_template = "fswebcam -d %s --jpeg 95 -r 640x480 %s";

    char command[256];
    snprintf(command, sizeof(command), command_template, device, output_file);

    printf("Ejecutando: %s\n", command);

    int ret = system(command);
    if (ret == -1) {
        perror("Error ejecutando fswebcam");
        return EXIT_FAILURE;
    }

    printf("Foto capturada en %s\n", output_file);

    return EXIT_SUCCESS;
}

