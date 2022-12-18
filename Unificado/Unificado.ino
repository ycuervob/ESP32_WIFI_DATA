#include <Arduino.h>
#include "utilities.h"

void setup() {
  Serial.begin(115200);
  gpsInicialization();
  tempInicialization();
  acelerometroInicializacion();
  termocuplaInicializacion();
  pinesyvariables();
  EncenderDispositivos();
  initSD();
  initGlobalVar();
}

void loop() {
  EncenderDispositivos();
  initSD();
  timeWrapper(tiempoLectura() * 1000, &almacenamientoDatos);
  initWIFI();
  delay(tiempoEsperaWifi());
  int tiempo_esp = tiempoEspera();
  timeWrapper(tiempoEnvio(tiempo_esp), &envioInformacion);
  ApagarDispositivos();
  timeWrapper(tiempo_esp, minAcelerometro(), &acelerometroAlto);
}