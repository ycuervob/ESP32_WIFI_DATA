#include <Arduino.h>
#include "src/variablesGlobalesUtilities.h"
#include "src/control/wrappers.h"
#include "src/func/generalUtilities.h"
#include "src/componentes/pinnesUtilities.h"
#include "src/componentes/acelerometroUtilities.h"
#include "src/componentes/gpsUtilities.h"
#include "src/componentes/tempUtilities.h"
#include "src/componentes/acelerometroUtilities.h"
#include "src/componentes/wifiUtilities.h"
#include "src/componentes/sdUtilities.h"
#include "src/componentes/termocuplaUtilities.h"

/**
 * @brief Funcion de inicio del programa.
 * 
 */
void setup() {
  gpsInicialization();
  tempInicialization();
  acelerometroInicializacion();
  termocuplaInicializacion();
  pinesyvariables();
  EncenderDispositivos();
  sdInicializacion();
  initGlobalVar();
  delay(getGlobalVar().tiempo_espera_modem);
  wifiInicializacion();
  initGrupoLectura();
}

/**
 * @brief Funcion que se ejecuta en un loop infinito.
 * 
 */
void loop() {
  EncenderDispositivos();
  sdInicializacion();
  timeWrapper(getGlobalVar().tiempo_lectura_guardado * 1000, &almacenamientoDatos);
  delay(getGlobalVar().tiempo_espera_modem);
  wifiInicializacion();
  int tiempo_esp = tiempoEspera();
  timeWrapper(tiempoEnvio(tiempo_esp), &envioInformacion);
  ApagarDispositivos();
  timeWrapper(tiempo_esp, getGlobalVar().acelerometro_anormal, &acelerometroAlto);
}