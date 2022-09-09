/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
#include <HardwareSerial.h>
#include <TinyGPS.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


//Setting Wifi settings for connection
const char* ssid = "UFI32";
const char* password = "1234567890";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.100.41:3000";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

//TinyGPSPlus gps
TinyGPS gps;
HardwareSerial SerialGPS(2);

void setup() {
  Serial.begin(115200);

  //GPS serial RX-> 16 , TX -> 17
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);

  //Wifi settings
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

}

void loop() {
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  // Checks if the GPS in sending data and if new data is received
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (SerialGPS.available())
    {
      char c = SerialGPS.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  // Read data from gps
  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");
    
    //Creating a JSON to post
    DynamicJsonDocument doc(1024);
    doc["sensor"] = "gps";
    doc["x"]   = flat;
    doc["y"] = flon;
    doc["age"] = age;

    //Dezerialize JSON to char * 
    char * postData;
    deserializeJson(doc, postData);
    int httpResponseCode = http.POST(postData);
   
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);   
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }

}
