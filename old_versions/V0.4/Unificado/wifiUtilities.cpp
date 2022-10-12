#include <WiFi.h>
#include <HTTPClient.h>
#include "utilities.h"

// Setting Wifi settings for connection
const char *ssid = "test";
const char *password = "clavetest";

// Your Domain name with URL path or IP address with path
const char *serverName = "http://54.94.206.91:80/";

void wifiInicializacion() {
  // Wifi settings
  WiFi.begin(ssid, password);
  int count = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    count++;
    if (count == 30) {
      ESP.restart();
      count = 0;
    }
  }
}

void httpmyRequest(String id_device_in, String bateria, String temperatura, String humedad, String flat, String flon, String timestamp, String numero_satelites, String varianza, double x, double y, double z, double total) {
  // Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");

    // JSON to send
        // JSON to send
    String postData = String("{ \"lista\":[") + String("\"") 
      + id_device_in + String("\",") 
      + bateria + String(",") 
      + temperatura + String(",") 
      + humedad + String(",") 
      + flat + String(",") 
      + flon + String(",") + String("\"") 
      + timestamp + String("\",") 
      + numero_satelites + String(",") 
      + varianza + String(",") 
      + String(x) +String(",") 
      + String(y) +String(",") 
      + String(z) +String(",") 
      + String(total) + String("]}");
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode < 0) {
      saveData(postData, httpResponseCode);
    } else {
      //Logica para encender un led mostrando que se guarda en la SD
    }
    http.end();
  } else {
    ESP.restart();
  }
}
