#include <DHT.h>
#define DHTTYPE DHT22
#define DHTPIN 4

DHT dht(DHTPIN, DHTTYPE, 22); // Función de temperatura

void tempInicialization(){
    dht.begin();
}

String *tempyhumedad()
{
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();
  Serial.println("Humedad: ");
  Serial.println(humedad);
  Serial.println("Temperatura: ");
  Serial.println(temperatura);

  String * strArray = new String[2];
  strArray[0] = String(temperatura, 6);
  strArray[1] = String(humedad, 6);
  return strArray;
}