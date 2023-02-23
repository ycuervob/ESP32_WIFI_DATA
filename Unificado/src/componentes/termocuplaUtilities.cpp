#include <OneWire.h>
#include <DallasTemperature.h>
#include "termocuplaUtilities.h"

// Pin donde se conecta el bus 1-Wire
const int pinDatosDQ = 15;

// Instancia a las clases OneWire
OneWire oneWireObjeto(pinDatosDQ);
// Instancia a la clase DallasTemperature para el manejo del sensór DS18B20
DallasTemperature sensorDS18B20(&oneWireObjeto);

/**
 * @brief Funcion que inicializa el sensor de temperatura.
 * 
 */
void termocuplaInicializacion(){
  // Iniciamos el bus 1-Wire
  sensorDS18B20.begin(); 
}

/**
 * @brief Funcion que obtiene la temperatura del sensor y la guarda en una estructura del tipo termocuplaDataType.
 * 
 * @param dataTermocupla ver dataTypes.h
 */
void termocupla(termocuplaDataType & dataTermocupla){
  sensorDS18B20.requestTemperatures(); 
  // Leemos y mostramos los datos de los sensores DS18B20
  String str_temperatura = String(sensorDS18B20.getTempCByIndex(0),6);
  dataTermocupla.temp = str_temperatura == "nan" ? "0.0" : str_temperatura;
   
}