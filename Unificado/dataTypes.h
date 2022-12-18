#include <Arduino.h>

#ifndef dataTypesproject
#define dataTypesproject

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

struct gpsDataType {
  String flat;
  String flon;
  String timestamp;
  String numero_satelites;
  String varianza;
  float velocidad;
};

struct temyhumDataType {
  String temperatura;
  String humedad;
};

struct acelerometroDataType {
  String x;
  String y;
  String z;
  String total;
};

struct paqueteDataType {
  String id_device;
  String bateria;
  temyhumDataType temyhDatos;
  gpsDataType gpsDatos;
  acelerometroDataType acelerometroDatos;
};

#endif