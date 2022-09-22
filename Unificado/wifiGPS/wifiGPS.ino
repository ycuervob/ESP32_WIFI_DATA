

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
#include <SPI.h>
#include <SD.h>
#include <DHT.h>      //Cargamos la librería DHT
#define DHTTYPE DHT22 // Definimos el modelo del sensor DHT22
#define DHTPIN 4      // Se define el pin D4 del ESP32 para conectar el sensor DHT22

// Control de encencido
int pinSD = 14;
int pinTem = 13;
int pinGps = 12;

byte x = 1; // Declaro una variable tipo byte

// Data from the device
const char *id_device = "ESP32LAB_TEST1";

// Setting Wifi settings for connection
const char *ssid = "LabLog";
const char *password = "17113467";

// Your Domain name with URL path or IP address with path
const char *serverName = "http://192.168.0.106:3000";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

// TinyGPSPlus gps
TinyGPS gps;
HardwareSerial SerialGPS(2);
DHT dht(DHTPIN, DHTTYPE, 22); // Función de temperatura

// Micro sd storage
File myFile;

void pinesyvariables()
{
  pinMode(pinSD, OUTPUT);
  pinMode(pinTem, OUTPUT);
  pinMode(pinGps, OUTPUT);
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Control de Encendido
  pinesyvariables();
  // GPS serial RX-> 16 , TX -> 17
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);

  // sd initialization
  Serial.print("Initializing SD card...");
  if (!SD.begin(5))
  {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");

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

  // Temperatura y humedad
  dht.begin();

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop()
{
  // Control de encendido
  while (x <= 5)
  { // Mientras x sea menor o igual a 5 ejecuto las instrucciones
    EncenderDispositivos();
    ProcesamientoDeInformacion(); // Procesamiento de información
    x = x + 1;                    // Incrementa en uno el valor de x
  }
  ApagarDispositivos();
  Serial.print("Tiempo de espera ");
  delay(30000);
  x = 1;
}

void EncenderDispositivos()
{
  //{period}: Periodo de Tiempo en el cual se va a ejecutar esta tarea
  unsigned long period = 2; // En Milisegundos

  static unsigned long previousMillis = 0;

  if ((millis() - previousMillis) > period)
  {
    digitalWrite(pinSD, HIGH);
    digitalWrite(pinTem, HIGH);
    digitalWrite(pinGps, HIGH);
    previousMillis += period;
  }
}
void ApagarDispositivos()
{
  //{period}: Periodo de Tiempo en el cual se va a ejecutar esta tarea
  unsigned long period = 2; // En Milisegundos

  static unsigned long previousMillis = 0;

  if ((millis() - previousMillis) > period)
  {
    digitalWrite(pinSD, LOW);
    digitalWrite(pinTem, LOW);
    digitalWrite(pinGps, LOW);
    previousMillis += period;
  }
}

void ProcesamientoDeInformacion()
{
  //{period}: Periodo de Tiempo en el cual se va a ejecutar esta tarea
  unsigned long period = 1000; // En Milisegundos

  static unsigned long previousMillis = 0;

  if ((millis() - previousMillis) > period)
  {
    // delay(1000);
    // Nivel de bateria
    int bateria = 100;

    // Timestamp
    char *timestamp = "2022-09-18 18:00:00";

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
    gps.stats(&chars, &sentences, &failed);

    flat = (flat == TinyGPS::GPS_INVALID_F_ANGLE) ? 0.0 : flat;
    flon = (flon == TinyGPS::GPS_INVALID_F_ANGLE) ? 0.0 : flon;
    int numero_satelites = (gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES) ? 0 : gps.satellites();
    float varianza = (gps.hdop() == TinyGPS::GPS_INVALID_HDOP) ? 0.0 : ((float)gps.hdop()) / 100;

    Serial.print("LAT=");
    Serial.print(flat, 6);
    Serial.print(" LON=");
    Serial.print(flon, 6);
    Serial.print(" SAT=");
    Serial.print(numero_satelites);
    Serial.print(" PREC=");
    Serial.print(varianza, 6);
    Serial.println();

    // tepmeratura y humedad
    float temperatura = dht.readTemperature();
    float humedad = dht.readHumidity();

    // Se imprimen las variables
    Serial.println("Humedad: ");
    Serial.println(humedad);
    Serial.println("Temperatura: ");
    Serial.println(temperatura);

    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/json");

      // JSON to send
      String postData = String("{ \"lista\":[") + String("\"") + String(id_device) + String("\",") + String(bateria) + String(",") + String(temperatura, 6) + String(",") + String(humedad, 6) + String(",") + String(flat, 6) + String(",") + String(flon, 6) + String(",") + String("\"") + String(timestamp) + String("\",") + String(numero_satelites) + String(",") + String(varianza) + String("]}");

      Serial.println(postData);
      int httpResponseCode = http.POST(postData);

      myFile = SD.open("/data.json", FILE_APPEND);

      if (httpResponseCode < 0)
      {
        Serial.print("Error sending data, storing in SD: ");
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
    }
    previousMillis += period;
  }
}
