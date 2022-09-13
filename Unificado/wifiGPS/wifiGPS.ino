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
#include <DHT.h>           //Cargamos la librería DHT


#define DHTTYPE  DHT22   //Definimos el modelo del sensor DHT22
#define DHTPIN    4     // Se define el pin D4 del ESP32 para conectar el sensor DHT22


//Setting Wifi settings for connection
const char* ssid = "Lablog";
const char* password = "17113467";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.100.41:3000";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

//TinyGPSPlus gps
TinyGPS gps;
HardwareSerial SerialGPS(2);
DHT dht(DHTPIN, DHTTYPE, 22);  // Función de temperatura

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

   // Temperatura y humedad
   dht.begin(); 
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

  gps.f_get_position(&flat, &flon, &age);
  Serial.print("LAT=");
  Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  Serial.print(" LON=");
  Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  Serial.print(" SAT=");
  Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
  Serial.print(" PREC=");
  Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0.0 : ((float) gps.hdop())/100 , 6);
  // Temperatura y humedad
  float h = dht.readHumidity(); //Se lee la humedad y se asigna el valor a "h"
  float t = dht.readTemperature(); //Se lee la temperatura y se asigna el valor a "t"
   //Se imprimen las variables
    Serial.println("Humedad: "); 
    Serial.println(h);
    Serial.println("Temperatura: ");
    Serial.println(t);
    delay(2000);  
    
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
