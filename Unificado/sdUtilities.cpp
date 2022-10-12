#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include <cstdlib>

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
  int string_len = postData.length() + 1;
  File myFile = SD.open("/data.json", FILE_APPEND);
  char Buf[string_len];

  postData.toCharArray(Buf, string_len);

  if (myFile) {
    myFile.println(Buf);
    datosGuardados = true;
  } else {
    datosGuardados = false;
    //Crear otro archivo?
  }
  myFile.close();
  return datosGuardados;
}

void getLine(int* position_var) {
  File fileLine = SD.open("/currentLine.txt");
  if (fileLine) {
    char value[fileLine.size()];
    fileLine.readBytes(value, fileLine.size());
    *position_var = atoi(value);
  }
}

void setLine(int* position_var){
  File fileLine = SD.open("/currentLine.txt",FILE_WRITE);
  if (fileLine) {
    fileLine.println(*position_var);
  }
  Serial.println(*position_var);
  Serial.read();
}

/**
  Lee una linea y retorna la posición en la que quedó (byte) al dejar de leer la linea.
  Estados:
    - ARCHIVO_NO_ABIERTO 0
    - LEIDO 1
    - NO_MAS_DATOS 2
*/
byte readLine(String* linea, int* posicion_var) {
  File myFile = SD.open("/data.json");
  byte linea_leida = 0;
  int fileSize = myFile.size();

  if (myFile && *posicion_var < fileSize) {
    myFile.seek(*posicion_var);
    *linea = myFile.readStringUntil('\n');
    *posicion_var = myFile.position();
    setLine(posicion_var);
    linea_leida = 1;
  } else if (*posicion_var >= fileSize) {
    linea_leida = 2;
    *posicion_var = 0;
    SD.remove("/currentLine.txt");
    SD.remove("/data.json");
  }

  delay(2000);
  myFile.close();
  return linea_leida;
}