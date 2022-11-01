#include <Arduino.h>
#include "utilities.h"
#include "wrappers.h"

const int pinBateria = 35;
byte x = 1;
byte y = 1;
int bateria = 0;
const char *id_device = "dispositivo_prueba";
const char *ssid = "test";
const char *password = "clavechida";
const char *serverName = "http://54.94.206.91:80/";

void almacenamientoDatos() {
  paqueteDataType dataToPost;
  tempyhumedad(dataToPost.temyhDatos);
  gpsDatos(dataToPost.gpsDatos);
  acelerometro(dataToPost.acelerometroDatos);
  dataToPost.bateria = analogRead(pinBateria);
  dataToPost.id_device = String(id_device);
  String postData = createPostData(dataToPost);
  byte status = pinWrapper(postData, &guardaDatosSD);

  unsigned long start = millis();
  while (status == NOT_SD) {
    endSD();
    sdInicializacion();
    status = pinWrapper(postData, &guardaDatosSD);
    if (millis() - start > 5000) {
      break;
    }
  }

  char *estados_general[4] = { "Datos erroneos, descartados", "No hay SD datos descartados", "Almacenado" };
  Serial.println(estados_general[status]);
  char Buf[postData.length() + 1];
  postData.toCharArray(Buf, postData.length() + 1);
  Serial.println(Buf);
}

/*
    - ARCHIVO_NO_ABIERTO 0
    - LEIDO 1
    - NO_MAS_DATOS 2
    - LEIDO_PERO_NO_ENVIADO 3
*/

void envioInformacion() {
  byte status = pinWrapper(serverName, ssid, password, &sendSDtoServer);
  char *estados_general[7] = { "ARCHIVO_NO_ABIERTO", "LEIDO", "NO_MAS_DATOS", "LEIDO_PERO_NO_ENVIADO", "FALLO_AL_ENVIAR", "ENVIADO", "NO_WIFI" };
  Serial.println(estados_general[status]);
}

void initSD() {
  bool init_sd = sdInicializacion();
  Serial.println(init_sd ? "si sd" : "no sd");
}


void initWIFI() {
  bool init_wifi = wifiInicializacion(ssid, password);
  Serial.println(init_wifi ? "si wifi" : "no wifi");
}