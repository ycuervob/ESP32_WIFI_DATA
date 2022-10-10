#include <SPI.h>
#include <SD.h>

// Micro sd storage
File myFile;

bool sdInitialization() {
  if (!SD.begin(SS)) {
    return false;
  }
  return true;
}

bool saveDataSD(String postData) {
  bool datosGuardados = false;
  myFile = SD.open("/data.json", FILE_APPEND);

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