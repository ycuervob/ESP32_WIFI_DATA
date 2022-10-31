#include <Arduino.h>

#ifndef dataTypesproject
#define dataTypesproject

struct gpsDataType {
  String flat;
  String flon;
  String timestamp;
  String numero_satelites;
  String varianza;
  String velocidad;
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

