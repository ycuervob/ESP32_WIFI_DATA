#include <Arduino.h>
#include "utilities.h"

/**
  Aquí no va nigún serial.prinln
*/
void setup() {
  //Serial.begin(115200);
  gpsInicialization();
  tempInicialization();
  acelerometroInicializacion();
  pinesyvariables();
}

void loop() {
  EncenderDispositivos();
  unionInicializacionWifiSD();
  timeWrapper(30000, &ProcesamientoDeInformacion);
  ApagarDispositivos();
  timeWrapper(300000,&acelerometroAlto);
}