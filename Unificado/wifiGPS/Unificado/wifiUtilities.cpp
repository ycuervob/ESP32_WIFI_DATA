

void wifiInicializacion()
{
    // Wifi settings
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    int count = 0;

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        count++;
        if (count == 30)
        {
            ESP.restart();
            count = 0;
        }
    }

    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void httpmyRequest(String id_device_in, String bateria, String temperatura, String humedad, String flat, String flon, String timestamp, String numero_satelites, String varianza)
{
  // Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("wifi Connected -------");
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");

    // JSON to send
    String postData = String("{ \"lista\":[") + String("\"") + id_device_in + String("\",") + bateria + String(",") + temperatura + String(",") + humedad + String(",") + flat + String(",") + flon + String(",") + String("\"") + timestamp + String("\",") + numero_satelites + String(",") + varianza + String("]}");
    Serial.println(postData);
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode < 0)
    {

      myFile = SD.open("/data.json", FILE_APPEND);
      Serial.print("Error sending data, storing in SD, http code: ");
      Serial.println(httpResponseCode);

      if (myFile)
      {
        Serial.print("Writing to data.json...");
        myFile.println(postData);
        myFile.close();
        Serial.println("done.");
      }
      else
      {
        Serial.println("error opening data.json");
        ESP.restart();
      }
    }
    else
    {
      Serial.print("Sended to the server, code: ");
      Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();
  }
  else
  {
    Serial.println("WiFi Disconnected");
    ESP.restart();
  }
}