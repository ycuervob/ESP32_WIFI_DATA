#include "WiFiType.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include "wifiUtilities.h"
#include "../variablesGlobalesUtilities.h"

/**
 * @brief Funcion que inicializa el wifi, retorna true si se conecta correctamente y false si no
 * Intenta conectarse por el tiempo especificado en globVars que se inicializa con base a los datos leidos de la micro sd.
 * Ver storeUtilities.cpp
 * 
 * @param ssid nombre de la red wifi
 * @param password contraseña de la red wifi
 * @return true 
 * @return false 
 */
bool wifiInicializacion(const char * ssid, const char * password) {
  WiFi.setAutoConnect(true);
  WiFi.setSleep(WIFI_PS_NONE);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);

  unsigned long start = millis();
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    if (millis() - start > getGlobalVar().tiempo_epera_conexion) { 
      return false;
    }
  }
  return true;
}

/**
 * @brief Recibe un archivo en formato apto para el servidor y lo envía por medio de una petición POST
  Retorna true si fue enviado correctamente y false si hubo algún error.
    - FALLO_AL_ENVIAR 4
    - ENVIADO 5
    - NO_WIFI 6
 * @param postData String datos a enviar
 * @param serverName const char * ip o url del servidor
 * @return byte
*/
byte httpmyRequest(String postData, const char * serverName) {
  byte data_sent_status = 6;
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode < 0) {
      data_sent_status = 4;
    } else {
      data_sent_status = 5;
    }

    http.end();
  } else {
    data_sent_status = 6;
  }

  return data_sent_status;
}