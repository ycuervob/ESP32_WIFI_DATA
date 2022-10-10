#include <DHT.h>
#include <Arduino.h>
#include "dataTypes.h"

#define DHTTYPE DHT22
#define DHTPIN 4

DHT dht(DHTPIN, DHTTYPE, 22);  // Función de temperatura

void
tempInicialization() {
  dht.begin();
}

temyhumDataType tempyhumedad() {
  temyhumDataType dataTyH;
  dataTyH.temperatura = String(dht.readTemperature()) == "nan" ? "0" : String(dht.readTemperature(), 6);
  dataTyH.humedad = String(dht.readHumidity()) == "nan" ? "0" : String(dht.readTemperature(), 6);
  return dataTyH;
}