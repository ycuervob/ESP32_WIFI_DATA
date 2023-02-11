#include <Arduino.h>
#include "src/control/wrappers.h"
#include "src/func/generalUtilities.h"
#include "src/componentes/pinnesUtilities.h"
#include "src/componentes/acelerometroUtilities.h"
#include "src/componentes/gpsUtilities.h"
#include "src/componentes/tempUtilities.h"
#include "src/componentes/acelerometroUtilities.h"
#include "src/componentes/termocuplaUtilities.h"

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