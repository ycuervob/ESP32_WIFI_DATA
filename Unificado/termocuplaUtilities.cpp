#include <OneWire.h>
#include <DallasTemperature.h>
#include "dataTypes.h"

// Pin donde se conecta el bus 1-Wire
const int pinDatosDQ = 2;

// Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

void termocuplaInicializacion(){
  // Iniciamos el bus 1-Wire
  sensorDS18B20.begin(); 
}

void termocupla(termocuplaDataType & dataTermocupla){
  sensorDS18B20.requestTemperatures(); 
  // Leemos y mostramos los datos de los sensores DS18B20
  dataTermocupla.temp = sensorDS18B20.getTempCByIndex(0); 
}