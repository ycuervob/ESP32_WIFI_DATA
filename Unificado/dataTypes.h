#include <Arduino.h>

#ifndef dataTypesproject
#define dataTypesproject

/**
 * @brief Estructura para guardar las variables globales que se usan en el programa y son leidas desde la microSD.
 * 
 * @param device String | Id del dispositivo
 * @param ssid String | Nombre de la red wifi a la que se conectará el dispositivo
 * @param pass String | Contraseña de la red wifi a la que se conectará el dispositivo
 * @param server String | Dirección del servidor al que se enviarán los datos
 * @param velocidad float | Velocidad a la que se mueve el dispositivo leida en el último ciclo
 * @param time_max int  | 
 * @param vel_max int | Velocidad máxima para no entrar en estado de reposo 
 * @param vel_min int | Velocidad mínima para entrar en estado de reposo el tiempo máximo
 * @param tiempo_lectura int | Tiempo en el que el dispositivo hará tantas lecturas como sea posible
 * @param max_tiempo_enviado int | Minimo tiempo que el dispositivo podrá tener para enviar datos.
 * @param porcentaje_enviado int | Porcentaje de tiempo que el dispositivo estará enviando datos, se refiere al denominador de la fracción
 * @param min_acelerometro_anormal int | Valor para determinar si dejar el estado de reposo ver acelerometroUtilities.cpp
 * @param tiempo_epera_conexion int | Tiempo de espera para intentar conectar con el servidor
 * @param tiempo_conexion_wifi int | Tiempo que el dispositivo estará intentando conectarse a la red wifi
 */
struct globVars {
  String device;
  String ssid;
  String pass;
  String server;
  float velocidad;
  int time_max;
  int vel_max;
  int vel_min;
  int tiempo_lectura;
  int max_tiempo_enviado;
  int porcentaje_enviado;
  int min_acelerometro_anormal;
  int tiempo_epera_conexion;
  int tiempo_conexion_wifi;
};

/**
 * @brief Estructura para guardar los datos del GPS
 * 
 * @param flat String | Latitud
 * @param flon String | Longitud
 * @param timestamp String | Fecha y hora
 * @param numero_satelites String | Número de satélites
 * @param varianza String | Varianza
 * @param velocidad float | Velocidad
 */
struct gpsDataType {
  String flat;
  String flon;
  String timestamp;
  String numero_satelites;
  String varianza;
  float velocidad;
};

/**
 * @brief Estructura para guardar los datos de temperatura y humedad
 * 
 * @param temperatura String | Temperatura
 * @param humedad String | Humedad
 */
struct temyhumDataType {
  String temperatura;
  String humedad;
};

/**
 * @brief Estructura para guardar los datos del acelerómetro
 * 
 * @param x String | Valor en x
 * @param y String | Valor en y
 * @param z String | Valor en z
 * @param total String | Valor total
 */
struct acelerometroDataType {
  String x;
  String y;
  String z;
  String total;
};

/**
 * @brief Estructura para guardar los datos de la termocupla
 * 
 * @param temp String | Temperatura
 */
struct termocuplaDataType{
  String temp;
};

/**
 * @brief Estructura para agrupar los datos que serán enviados al servidor mediante un POST
 * 
 * @param bateria String | Porcentaje de batería
 * @param temyhDatos temyhumDataType | Datos de temperatura y humedad
 * @param gpsDatos gpsDataType | Datos del GPS
 * @param acelerometroDatos acelerometroDataType | Datos del acelerómetro
 * @param termocuplaDatos termocuplaDataType | Datos de la termocupla
 */
struct paqueteDataType {
  String id_device;
  String bateria;
  temyhumDataType temyhDatos;
  gpsDataType gpsDatos;
  acelerometroDataType acelerometroDatos;
  termocuplaDataType termocuplaDatos;
};

#endif