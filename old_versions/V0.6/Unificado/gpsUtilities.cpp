#include <TinyGPS.h>

// TinyGPSPlus gps
TinyGPS gps;
HardwareSerial SerialGPS(2);

void gpsInicialization(){
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17); // GPS serial RX-> 16 , TX -> 17
}

String *gpsDatos()
{
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
    for (unsigned long start = millis(); millis() - start < 1000;)
    {
        while (SerialGPS.available())
        {
            char c = SerialGPS.read();
            //Serial.write(c);
            if (gps.encode(c)) // Did a new valid sentence come in?
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

    String * strArray2 = new String[5];
    strArray2[0] = String(flat, 6);
    strArray2[1] = String(flon, 6);
    strArray2[2] = String(timestamp);
    strArray2[3] = String(numero_satelites);
    strArray2[4] = String(varianza);

    return strArray2;
}