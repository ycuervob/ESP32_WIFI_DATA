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
#include <DHT.h>
#define DHTTYPE DHT22
#define DHTPIN 4
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Control de encencido
int pinSD = 14;
int pinTem = 13;
int pinGps = 12;

byte x = 1;
byte y = 1;

// Data from the device
const String id_device = "dispositivo_prueba";

// Setting Wifi settings for connection
const char *ssid = "test";
const char *password = "clavetest";

// Your Domain name with URL path or IP address with path
const char *serverName = "http://54.94.206.91";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

// TinyGPSPlus gps
TinyGPS gps;
HardwareSerial SerialGPS(2);
DHT dht(DHTPIN, DHTTYPE, 22);  // Función de temperatura

// Micro sd storage
File myFile;

// Accelerometer
Adafruit_MPU6050 mpu;

void pinesyvariables() {
  pinMode(pinSD, OUTPUT);
  pinMode(pinTem, OUTPUT);
  pinMode(pinGps, OUTPUT);
}

void sdInitialization() {

  Serial.print("Initializing SD card...");
  if (!SD.begin(SS)) {
    Serial.println("initialization failed!");
    ESP.restart();
  }
  Serial.println("initialization done.");
}

void EncenderDispositivos() {
  digitalWrite(pinSD, HIGH);
  digitalWrite(pinTem, HIGH);
  digitalWrite(pinGps, HIGH);
}

void ApagarDispositivos() {
  digitalWrite(pinSD, LOW);
  digitalWrite(pinTem, LOW);
  digitalWrite(pinGps, LOW);
}

void acelerometro(double *array_ace) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  Serial.print("Acceleration Total: ");
  Serial.println(sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)));
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  double acceArray[3] = { a.acceleration.x, a.acceleration.y, a.acceleration.x };
  array_ace = acceArray;
}

String * gpsDatos() {
  // Read data from gps
  unsigned long chars;
  unsigned short sentences, failed;
  bool newData = false;
  float flat, flon;
  unsigned long age;
  int year;
  byte month, day, hour, minute, second, hundredths;

  // For one second we parse GPS data and report some key values
  // Checks if the GPS in sending data and if new data is received
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (SerialGPS.available()) {
      char c = SerialGPS.read();
      if (gps.encode(c))  // Did a new valid sentence come in?
        newData = true;
    }
  }

  gps.f_get_position(&flat, &flon, &age);
  gps.stats(&chars, &sentences, &failed);
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  char timestamp[32];
  sprintf(timestamp, "%02d/%02d/%02d %02d:%02d:%02d ", month, day, year, hour, minute, second);

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

  String strArray2[5] = { String(flat, 6), String(flon, 6), String(timestamp), String(numero_satelites), String(varianza) };
  return strArray2;
}

String * tempyhumedad() {
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();
  Serial.println("Humedad: ");
  Serial.println(humedad);
  Serial.println("Temperatura: ");
  Serial.println(temperatura);

  String strArray[2] = { String(temperatura, 6), String(humedad, 6) };
  return strArray;
}

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

      myFile = SD.open("/data.json", FILE_APPEND);
      Serial.print("Error sending data, storing in SD, http code: ");
      Serial.println(httpResponseCode);

      if (myFile) {
        Serial.print("Writing to data.json...");
        myFile.println(postData);
        myFile.close();
        Serial.println("done.");
      } else {
        Serial.println("error opening data.json");
        ESP.restart();
      }
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

void acelerometroInicializacion() {
  // acc initialization
  Serial.begin(115200);
  while (!Serial)
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }
}

void ProcesamientoDeInformacion() {
  int bateria = 100;
  String *array_tempyhym = tempyhumedad();
  String *array_gpsDatos = gpsDatos();
  //double array_acelerometro[3] = {-1,-1,-1};
  //acelerometro(array_acelerometro);
  Serial.println(id_device);
  Serial.println(bateria);
  Serial.println(array_tempyhym[0]);
  Serial.println(array_tempyhym[1]);
  Serial.println(array_gpsDatos[0]);
  Serial.println(array_gpsDatos[1]);
  Serial.println(array_gpsDatos[2]);
  Serial.println(array_gpsDatos[3]);
  Serial.println(array_gpsDatos[4]);
  //httpmyRequest(id_device, String(bateria), array_tempyhym[0], array_tempyhym[1], array_gpsDatos[0], array_gpsDatos[1], array_gpsDatos[2], array_gpsDatos[3], array_gpsDatos[4]);
}

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);  // GPS serial RX-> 16 , TX -> 17
  wifiInicializacion();
  dht.begin();
  acelerometroInicializacion();
  pinesyvariables();
  EncenderDispositivos();
  sdInitialization();
}

void loop() {
  // Control de encendido
  EncenderDispositivos();
  sdInitialization();
  while (x <= 15) {                // Mientras x sea menor o igual a 5 ejecuto las instrucciones
    ProcesamientoDeInformacion();  // Procesamiento de información
    x = x + 1;                     // Incrementa en uno el valor de x
  }
  ApagarDispositivos();
  delay(10000);
}