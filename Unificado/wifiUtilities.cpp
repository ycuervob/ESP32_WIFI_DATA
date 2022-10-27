#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

const char *ssid = "FIPROTECTION_C";
const char *password = "DX-120USBBLACKG55";
const char *serverName = "http://54.94.206.91:80/";

bool wifiInicializacion() {
  WiFi.setAutoConnect(true);
  WiFi.setSleep(WIFI_PS_NONE);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);

  unsigned long start = millis();
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    if (millis() - start > 10000) {  // Se intenta conectar por 30 segundos
      return false;
    }
  }
  return true;
}

/**
  Recibe un archivo en formato apto para el servidor y lo envía por medio de una petición POST
  Retorna true si fue enviado correctamente y false si hubo algún error.
*/
bool httpmyRequest(String postData) {
  bool data_sent_correct = false;
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode < 0) {
      data_sent_correct = false;
    } else {
      data_sent_correct = true;
    }

    http.end();
  } else {
    //Se trata de conectar cada vez que ve que no tiene WIFI
    data_sent_correct = false;
  }
  return data_sent_correct;
}