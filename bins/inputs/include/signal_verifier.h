#ifndef SIGNAL_VERIFIER_H
#define SIGNAL_VERIFIER_H

// Define el consumidor de GPIO
#define CONSUMER "signal_verifier"

// Función para leer el estado de un pin GPIO
// Retorna:
//  0 si el pin está en ALTO (HIGH)
//  1 si el pin está en BAJO (LOW)
//  2 si hubo un error
int signal_verifier(int pin);


#endif

