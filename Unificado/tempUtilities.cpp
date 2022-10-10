#include <DHT.h>
#include <Arduino.h>
#include "dataTypes.h" 

#define DHTTYPE DHT22
#define DHTPIN 4

DHT dht(DHTPIN, DHTTYPE, 22);  // Función de temperatura

void tempInicialization() {
  dht.begin();
}

temyhumDataType tempyhumedad() {
  temyhumDataType dataTyH;
  String str_temperatura = String(dht.readTemperature(),6);
  String str_humedad = String(dht.readHumidity(),6);
  dataTyH.temperatura = str_temperatura == "nan" ? "0" : str_humedad;
  dataTyH.humedad = str_humedad == "nan" ? "0" : str_humedad;
  return dataTyH;
}