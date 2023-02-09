#include <DHT.h>
#include <Arduino.h>
#include "dataTypes.h" 
#define DHTTYPE DHT22
#define DHTPIN 4

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE, 22);  

/**
 * @brief Funcion que inicializa el sensor de temperatura y humedad.
 * 
 */
void tempInicialization() {
  dht.begin();
}

/**
 * @brief Funcion que obtiene la temperatura y humedad.
 * 
 * @param dataTyH ver dataTypes.h
 */
void tempyhumedad(temyhumDataType & dataTyH){
  String str_temperatura = String(dht.readTemperature(),6);
  String str_humedad = String(dht.readHumidity(),6);
  dataTyH.temperatura = str_temperatura == "nan" ? "0" : str_temperatura;
  dataTyH.humedad = str_humedad == "nan" ? "0" : str_humedad;
}