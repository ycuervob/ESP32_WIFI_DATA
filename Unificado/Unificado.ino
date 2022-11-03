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
  timeWrapper(30 * 1000, &almacenamientoDatos);
  initWIFI();
  int tiempo_esp = tiempoEspera();
  int t_WIFI = (tiempo_esp / 5) >= 60 * 1000 ? (tiempo_esp / 5) : 0;
  timeWrapper(t_WIFI, &envioInformacion);
  ApagarDispositivos();
  timeWrapper(tiempo_esp, &acelerometroAlto);
}