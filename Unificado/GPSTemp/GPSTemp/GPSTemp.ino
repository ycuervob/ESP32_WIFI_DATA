#include <Arduino.h>
#include <HardwareSerial.h>
#include <TinyGPS.h>
#include <DHT.h>           //Cargamos la librería DHT
#define DHTTYPE  DHT22   //Definimos el modelo del sensor DHT22
#define DHTPIN    4     // Se define el pin D4 del ESP32 para conectar el sensor DHT22

//TinyGPSPlus gps;
TinyGPS gps;
HardwareSerial SerialGPS(2);
DHT dht(DHTPIN, DHTTYPE, 22); 

void setup() {
  Serial.begin(115200);          // RX  TX
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
    dht.begin(); 
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  float h = dht.readHumidity(); //Se lee la humedad y se asigna el valor a "h"
  float t = dht.readTemperature(); //Se lee la temperatura y se asigna el valor a "t"


  // For one second we parse GPS data and report some key values
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


  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  Serial.print("LAT=");
  Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  Serial.print(" LON=");
  Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  Serial.print(" SAT=");
  Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
  Serial.print(" PREC=");
  Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0.0 : ((float) gps.hdop())/100 , 6);

  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **"); 
   //Se imprimen las variables
  delay(1000);  
  Serial.print("Humedad: "); 
  Serial.print(h);
  Serial.print("Temperatura: ");
  Serial.print(t);

  
 
}



/*void loop() {

  Serial.println("------------");
  Serial.print("available(): ");
  Serial.println(SerialGPS.available());
  Serial.println("------------");
  while (SerialGPS.available() > 0) {
    char c = SerialGPS.read();
    Serial.print(c);
    gps.encode(c);
  }
  Serial.println();

    Serial.print("LAT=");
    Serial.println(gps.location.lat(), 6);
    Serial.print("LONG=");
    Serial.println(gps.location.lng(), 6);
    Serial.print("ALT=");
    Serial.println(gps.altitude.meters());
    Serial.println(gps.time.value()); // Raw time in HHMMSSCC format (u32)
    Serial.println(gps.time.hour()); // Hour (0-23) (u8)  
    Serial.println(gps.time.minute()); // Minute (0-59) (u8)  
    Serial.println(gps.time.second()); // Second (0-59) (u8)   
     Serial.println(gps.satellites.value()); // Number of satellites in use (u32)


  delay(1000);
}*/
