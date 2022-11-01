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
  timeWrapper(60000, &almacenamientoDatos);
  initWIFI();
  timeWrapper(60000, &envioInformacion);
  ApagarDispositivos();
  timeWrapper(10000,&acelerometroAlto);
}