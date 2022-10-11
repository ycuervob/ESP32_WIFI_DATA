#include <SPI.h>
#include <SD.h>
#include <Arduino.h>

bool sdInicializacion() {
  if (!SD.begin(SS)) {
    return false;
  }
  return true;
}

/**
  Recibe un String y lo almacena el archivo data.json de la micro sd.
    Retorna true si se guardo y false de lo contrario.
*/
bool saveDataSD(String postData) {
  bool datosGuardados = false;
  File myFile = SD.open("/data.json", FILE_APPEND);

  if (myFile) {
    myFile.println(postData);
    datosGuardados = true;
  } else {
    datosGuardados = false;
    //Crear otro archivo?
  }
  delay(2000);
  myFile.close();
  return datosGuardados;
}

/**
  Lee una linea y retorna la posición en la que quedó (byte) al dejar de leer la linea.
  Estados:
    - ARCHIVO_NO_ABIERTO 0
    - LEIDO 1
    - NO_MAS_DATOS 2
*/
byte readLine(String* linea, int* posicion) {
  File myFile = SD.open("/data.json");
  byte linea_leida = 0;
  int fileSize = myFile.size();

  if (myFile && *posicion < fileSize) {
    myFile.seek(*posicion);
    *linea = myFile.readStringUntil('\n');
    *posicion = myFile.position();
    linea_leida = 1;
  } else if (*posicion >= fileSize) {
    linea_leida = 2;
    *posicion = 0;
    SD.remove("/data.json");
  }

  delay(2000);
  myFile.close();
  return linea_leida;
}