#include <Arduino.h>

#ifndef dataTypesproject
#define dataTypesproject

struct globVars {
  String device;
  String ssid;
  String pass;
  String server;
  float velocidad;
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