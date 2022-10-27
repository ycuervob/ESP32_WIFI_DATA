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
  unionInicializacionWifiSD();
  timeWrapper(20000, &almacenamientoDatos);
  timeWrapper(20000, &envioInformacion);
  ApagarDispositivos();
  timeWrapper(10000,&acelerometroAlto);
}