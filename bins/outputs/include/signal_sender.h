#ifndef SIGNAL_SENDER_H
#define SIGNAL_SENDER_H

// Define el consumidor de GPIO
#define CONSUMER "gpio-output-control"

// Lista de pines de salida permitidos
extern int output_pins[];
extern int output_count;

// Función que verifica si un pin es válido para salida
int pin_es_valido(int pin);

// Función para establecer el valor de un pin GPIO de salida
// Retorna:
//  0 en éxito
//  1 en error
int set_gpio_output(int pin, int value);

#endif

