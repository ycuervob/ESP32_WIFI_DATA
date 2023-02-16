#ifndef dataTypesproject
#define dataTypesproject

#include <Arduino.h>

/**
 * @brief Estructura para guardar las variables globales que se usan en el programa y son leidas desde la microSD.
 * 
 * @param device String | Id del dispositivo
 * @param ssid String | Nombre de la red wifi a la que se conectará el dispositivo
 * @param pass String | Contraseña de la red wifi a la que se conectará el dispositivo
 * @param server String | Dirección del servidor al que se enviarán los datos
 * @param velocidad float | Velocidad a la que se mueve el dispositivo leida en el último ciclo
 * @param tiempo_max int  | Tiempo máximo que el dispositivo tendrá y que luego dividirá en tiempo de envío y tiempo de espera
 * @param vel_no_reposo int | Velocidad desde la cual no se entra en estado de reposo 
 * @param vel_reposo_max int | Velocidad mas baja desde la cual se entra en estado de reposo 
 * @param tiempo_lectura_guardado int | Tiempo en el que el dispositivo hará tantas lecturas como sea posible y las almacenará en la microSD
 * @param min_tiempo_enviado int | Minimo tiempo que el dispositivo podrá tener para enviar datos por debajo de eso el dispositivo no envía datos
 * @param porcentaje_enviado int | Denominador de la fracción de tiempo_max que es el tiempo que se usará para enviar datos 
 * @param acelerometro_anormal int | Valor de aceleración para determinar si dejar el estado de reposo ver acelerometroUtilities.cpp
 * @param tiempo_epera_conexion int | Tiempo que el dispositovo esperará al modem wifi a que esté disponible.
 * @param tiempo_espera_modem int | Tiempo que el dispositovo esperará al modem wifi a que esté disponible.
 */
struct globVars {
  String device;
  String ssid;
  String pass;
  String server;
  float velocidad;
  int tiempo_max;
  int vel_no_reposo;
  int vel_reposo_max;
  int tiempo_lectura_guardado;
  int min_tiempo_enviado;
  int porcentaje_enviado;
  int acelerometro_anormal;
  int tiempo_epera_conexion;
  int tiempo_espera_modem;
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