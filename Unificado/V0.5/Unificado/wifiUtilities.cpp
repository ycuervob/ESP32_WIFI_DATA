#include <WiFi.h>
#include <HTTPClient.h>
#include "utilities.h"

// Setting Wifi settings for connection
const char *ssid = "LabLog";
const char *password = "17113467";

// Your Domain name with URL path or IP address with path
const char *serverName = "http://54.94.206.91:80/";

bool wifiInicializacion() {
  // Wifi settings
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  int count = 0;

  unsigned long start = millis();
  Serial.println("Conectando ...");
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - start > 10000) {  // Se intenta conectar por 15 segundos
      Serial.println("NO se pudo conectar");
      return false;
    }
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  return true;
}

void httpmyRequest(String id_device_in, String bateria, String temperatura, String humedad, String flat, String flon, String timestamp, String numero_satelites, String varianza, double x, double y, double z, double total) {
  // JSON to send

  if(flat == String("0.000000")|| flat == String("0.000000")){
    return; // No envia datos donde el gps no esté funcionando o alun dato esté mal
  }

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
                    + String(x) + String(",")
                    + String(y) + String(",")
                    + String(z) + String(",")
                    + String(total) + String("]}");
  Serial.println(postData);

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("wifi Connected -------");
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode < 0) {
      saveData(postData, httpResponseCode);
    } else {
      Serial.print("Sended to the server, code: ");
      Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
    saveData(postData, -100);
  }
}