/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
#include "utilities.h"

byte x = 1;
byte y = 1;

// Data from the device
const String id_device = "dispositivo_prueba";

void ProcesamientoDeInformacion() {
  int bateria = 100;
  String *array_tempyhym = tempyhumedad();
  String *array_gpsDatos = gpsDatos();
  double *array_acelerometro = acelerometro();
  Serial.println(id_device);
  Serial.println(bateria);
  Serial.println(array_tempyhym[0]);
  Serial.println(array_tempyhym[1]);
  Serial.println(array_gpsDatos[0]);
  Serial.println(array_gpsDatos[1]);
  Serial.println(array_gpsDatos[2]);
  Serial.println(array_gpsDatos[3]);
  Serial.println(array_gpsDatos[4]);
  httpmyRequest(id_device, String(bateria), array_tempyhym[0], array_tempyhym[1], array_gpsDatos[0], array_gpsDatos[1], array_gpsDatos[2], array_gpsDatos[3], array_gpsDatos[4]);
  delete[] array_gpsDatos;
  delete[] array_acelerometro;
  delete[] array_tempyhym;
}


void setup() {
  Serial.begin(115200);
  gpsInicialization();
  wifiInicializacion();
  tempInicialization();
  acelerometroInicializacion();
  pinesyvariables();
  EncenderDispositivos();
  sdInitialization();
}

void loop() {
  // Control de encendido
  EncenderDispositivos();
  sdInitialization();
  while (x <= 15) {                // Mientras x sea menor o igual a 5 ejecuto las instrucciones
    ProcesamientoDeInformacion();  // Procesamiento de información
    x = x + 1;                     // Incrementa en uno el valor de x
  }
  ApagarDispositivos();
  delay(10000);
}