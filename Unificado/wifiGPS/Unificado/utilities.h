#include <SPI.h>
#include <SD.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <HardwareSerial.h>
#include <TinyGPS.h>

// TinyGPSPlus gps
TinyGPS gps;
HardwareSerial SerialGPS(2);

// Control de encencido
int pinSD = 14;
int pinTem = 13;
int pinGps = 12;

#define DHTTYPE DHT22
#define DHTPIN 4

// Micro sd storage
File myFile;

DHT dht(DHTPIN, DHTTYPE, 22); // Función de temperatura

// Setting Wifi settings for connection
const char *ssid = "test";
const char *password = "clavetest";

// Your Domain name with URL path or IP address with path
const char *serverName = "http://54.94.206.91";

// Accelerometer
Adafruit_MPU6050 mpu;