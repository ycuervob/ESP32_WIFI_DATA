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
  timeWrapper(30000, &almacenamientoDatos);
  initWIFI();
  timeWrapper(tiempoEspera() * 0.2 > 60000 ? tiempoEspera() * 0.2 : 0, &envioInformacion);
  ApagarDispositivos();
  timeWrapper(tiempoEspera(), &acelerometroAlto);
}