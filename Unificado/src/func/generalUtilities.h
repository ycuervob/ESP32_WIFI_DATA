#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>

// Declaración de funciones
int tiempoEspera();
int tiempoLectura();
int minAcelerometro();
int tiempoEsperaWifi();
int tiempoConexionWifi();
int tiempoEnvio(int);
void initGlobalVar();
void almacenamientoDatos();
void initWIFI();
void initSD();
byte envioInformacion();

#endif // UTILITIES_H
