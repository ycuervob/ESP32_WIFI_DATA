#include <Arduino.h>
#include "utilities.h"

/**
  Aquí no va nigún serial.prinln
*/
void setup() {
  Serial.begin(115200);
  gpsInicialization();
  tempInicialization();
  acelerometroInicializacion();
  pinesyvariables();
}

void loop() {
  EncenderDispositivos();
  initSD();
  initGlobalVar();
  timeWrapper(tiempoLectura() * 1000, &almacenamientoDatos);
  initWIFI();
  int tiempo_esp = tiempoEspera();
  timeWrapper(tiempoEnvio(tiempo_esp), &envioInformacion);
  ApagarDispositivos();
  timeWrapper(tiempo_esp, &acelerometroAlto);
}