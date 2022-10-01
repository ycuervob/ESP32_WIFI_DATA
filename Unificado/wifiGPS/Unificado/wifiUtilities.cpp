#include <WiFi.h>
#include <HTTPClient.h>
#include "utilities.h"

// Setting Wifi settings for connection
const char *ssid = "test";
const char *password = "clavetest";

// Your Domain name with URL path or IP address with path
const char *serverName = "http://54.94.206.91";

void wifiInicializacion() {
  // Wifi settings
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  int count = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    count++;
    if (count == 30) {
      ESP.restart();
      count = 0;
    }
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void httpmyRequest(String id_device_in, String bateria, String temperatura, String humedad, String flat, String flon, String timestamp, String numero_satelites, String varianza) {
  // Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("wifi Connected -------");
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");

    // JSON to send
    String postData = String("{ \"lista\":[") + String("\"") + id_device_in + String("\",") + bateria + String(",") + temperatura + String(",") + humedad + String(",") + flat + String(",") + flon + String(",") + String("\"") + timestamp + String("\",") + numero_satelites + String(",") + varianza + String("]}");
    Serial.println(postData);
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
    ESP.restart();
  }
}