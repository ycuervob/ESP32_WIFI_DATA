#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

// Setting Wifi settings for connection
const char *ssid = "LabLog";
const char *password = "17113467";

// Your Domain name with URL path or IP address with path
const char *serverName = "http://54.94.206.91:80/";

bool wifiInicializacion() {
  // Wifi settings
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
  }

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - start > 10000) {  // Se intenta conectar por 10 segundos
      return false;
    }
  }
  return true;
}

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
    wifiInicializacion();
    data_sent_correct = false;
  }

  return data_sent_correct;
}