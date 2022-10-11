#include <TinyGPS.h>
#include <Arduino.h>
#include "dataTypes.h"


// TinyGPSPlus gps
TinyGPS gps;
HardwareSerial SerialGPS(2);

void gpsInicialization() {
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);  // GPS serial RX-> 16 , TX -> 17
}

void gpsDatos(gpsDataType& dataGps) {
  // Read data from gps
  unsigned long chars;
  unsigned short sentences, failed;
  bool newData = false;
  float flon, flat;
  unsigned long age;
  int year;
  byte month, day, hour, minute, second, hundredths;

  // For one second we parse GPS data and report some key values
  // Checks if the GPS in sending data and if new data is received
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (SerialGPS.available()) {
      char c = SerialGPS.read();
      //Serial.write(c);
      if (gps.encode(c))
        newData = true;
    }
  }

  gps.f_get_position(&flat, &flon, &age);
  gps.stats(&chars, &sentences, &failed);
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  char timestamp[32];

  sprintf(timestamp, "%02d/%02d/%02d %02d:%02d:%02d ", month, day, year, hour, minute, second);
  dataGps.timestamp = String(timestamp);
  dataGps.flat = (flat == TinyGPS::GPS_INVALID_F_ANGLE) ? "0.0" : String(flat, 6);
  dataGps.flon = (flon == TinyGPS::GPS_INVALID_F_ANGLE) ? "0.0" : String(flon, 6);
  dataGps.numero_satelites = (gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES) ? "0" : String(gps.satellites(), 6);
  dataGps.varianza = (gps.hdop() == TinyGPS::GPS_INVALID_HDOP) ? "0.0" : String(((float)gps.hdop() / 100),6);
}