#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

// Setting Wifi settings for connection
const char *ssid = "Redmi999";
const char *password = "clavechida";

// Your Domain name with URL path or IP address with path
const char *serverName = "http://54.94.206.91:80/";

bool wifiInicializacion() {
  // Wifi settings
  
  WiFi.begin(ssid, password);
 
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - start > 5000) {  // Se intenta conectar por 30 segundos
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