#include <SPI.h>
#include <SD.h>
#include <Arduino.h>

bool sdInicializacion() {
  if (!SD.begin(SS)) {
    return false;
  }
  return true;
}

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
  Retorna puntero a instancia de FILE

File* fileInstance() {
  File myFile = SD.open("/data.json");
  return &myFile;
}
*/