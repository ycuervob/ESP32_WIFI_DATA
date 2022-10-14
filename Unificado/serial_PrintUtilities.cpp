#include <Arduino.h>
bool serial_inincialized = false;
char* estados_general[4] = { "Datos erroneos, descartados", "Fallo al enviar al servidor, guardado en SD", "No hay wifi ni SD --", "Enviado al servidor" };
char* estados_SDtoWIFI[4] = { "Archivo no abierto, se descarta dato", "Leido", "No hay mas datos en la SD", "El dato fue leido pero no enviado, se descarta" };

