#include <Arduino.h>
#include "utilities.h"

/**
 * @brief Funcion de inicio del programa.
 * 
 */
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

/**
 * @brief Funcion que se ejecuta en un loop infinito.
 * 
 */
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