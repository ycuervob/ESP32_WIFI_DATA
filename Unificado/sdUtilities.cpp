#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include <cstdlib>

File myFile, fileLine;

void initGlobalVar(const char* id_device, const char* ssid, const char* password, const char* serverName) {
  File fileSsid, filePassword, fileServerName, fileId_device;
  File* listFiles[4] = { &fileId_device, &fileSsid, &filePassword, &fileServerName };
  char* nameFiles[4] = { "/id_device.txt", "/ssid.txt", "/password.txt", "/fileServerName.txt" };
  const char** vars[4] = { &id_device, &ssid, &password, &serverName };

  for (int i = 0; i < 4; i++) {
    *listFiles[i] = SD.open(nameFiles[i], FILE_READ);
    if (*listFiles[i]) {
      char value[listFiles[i]->size()];

      listFiles[i]->readBytes(value, listFiles[i]->size());

      Serial.println(nameFiles[i]);
      Serial.println(value);
      *vars[i] = value;
      Serial.println(*vars[i]);
    }
    listFiles[i]->close();
  }
}

bool sdInicializacion(const char* id_device, const char* ssid, const char* password, const char* serverName) {
  unsigned long start = millis();
  while (!SD.begin(SS)) {
    if (millis() - start > 5000) {  // Se intenta conectar por 10 segundos
      return false;
    }
  }
  initGlobalVar(id_device, ssid, password, serverName);
  return true;
}

void endSD() {
  SD.end();
  delay(200);
}



/**
  Recibe un String y lo almacena el archivo data.json de la micro sd.
    Retorna true si se guardo y false de lo contrario.
*/
bool saveDataSD(String postData) {
  myFile = SD.open("/data.json", FILE_APPEND);
  bool datosGuardados = false;
  int string_len = postData.length() + 1;
  char Buf[string_len];
  postData.toCharArray(Buf, string_len);

  if (myFile) {
    myFile.println(Buf);
    datosGuardados = true;
  } else {
    datosGuardados = false;
  }

  myFile.close();
  return datosGuardados;
}

void getLine(int* position_var) {
  fileLine = SD.open("/currentLine.txt");
  if (fileLine) {
    char value[fileLine.size()];
    fileLine.readBytes(value, fileLine.size());
    *position_var = atoi(value);
  }
  fileLine.close();
}

void setLine(int* position_var) {
  fileLine = SD.open("/currentLine.txt", FILE_WRITE);
  if (fileLine) {
    fileLine.println(*position_var);
  }
  fileLine.close();
  //Serial.println(*position_var);  //IMPORTANTE COMENTAR ESTA LINEA ----------------
}

/**
  Lee una linea y retorna la posición en la que quedó (byte) al dejar de leer la linea.
  Estados:
    - ARCHIVO_NO_ABIERTO 0
    - LEIDO 1
    - NO_MAS_DATOS 2
*/
byte readLine(String* linea, int* posicion_var) {
  myFile = SD.open("/data.json");
  byte linea_leida = 0;
  int fileSize = myFile.size();

  if (myFile) {
    if (*posicion_var < fileSize) {
      myFile.seek(*posicion_var);
      *linea = myFile.readStringUntil('\n');
      *posicion_var = myFile.position();
      setLine(posicion_var);
      linea_leida = 1;
      myFile.close();
      return linea_leida;
    } else if (*posicion_var >= fileSize) {
      linea_leida = 2;
      *posicion_var = 0;
      myFile.close();
      SD.remove("/currentLine.txt");
      SD.remove("/data.json");
      return linea_leida;
    }
  }

  myFile.close();
  delay(2000);
  return linea_leida;
}