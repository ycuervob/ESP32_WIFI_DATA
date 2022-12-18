#include "WiFiType.h"
#include "utilities.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

bool wifiInicializacion(const char * ssid, const char * password) {
  WiFi.setAutoConnect(true);
  WiFi.setSleep(WIFI_PS_NONE);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);

  unsigned long start = millis();
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    if (millis() - start > tiempoConexionWifi()) {  // Se intenta conectar por 30 segundos
      return false;
    }
  }
  return true;
}

/**
  Recibe un archivo en formato apto para el servidor y lo envía por medio de una petición POST
  Retorna true si fue enviado correctamente y false si hubo algún error.
    - FALLO_AL_ENVIAR 4
    - ENVIADO 5
    - NO_WIFI 6
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
    //Se trata de conectar cada vez que ve que no tiene WIFI
    data_sent_status = 6;
  }

  return data_sent_status;
}