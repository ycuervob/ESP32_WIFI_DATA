#include <Arduino.h>
#include "utilities.h"

const int pinBateria = 35;
byte x = 1;
byte y = 1;
int bateria = 0;
const char* id_device;
const char* ssid;
const char* password;
const char* serverName;

void almacenamientoDatos() {
  paqueteDataType dataToPost;
  tempyhumedad(dataToPost.temyhDatos);
  gpsDatos(dataToPost.gpsDatos);
  acelerometro(dataToPost.acelerometroDatos);
  dataToPost.bateria = analogRead(pinBateria);
  dataToPost.id_device = String(id_device);
  Serial.println(id_device);
  Serial.println(ssid);
  Serial.println(password);
  Serial.println(serverName);

  String postData = createPostData(dataToPost);
  byte status = pinWrapper(postData, &guardaDatosSD);

  unsigned long start = millis();
  while (status == NOT_SD) {
    endSD();
    sdInicializacion(id_device, ssid, password, serverName);
    status = pinWrapper(postData, &guardaDatosSD);
    if (millis() - start > 5000) {
      break;
    }
  }

  char* estados_general[4] = { "Datos erroneos, descartados", "Fallo al enviar al servidor, guardado en SD", "No hay wifi ni SD --", "Enviado al servidor" };
  Serial.println(estados_general[status]);
  char Buf[postData.length() + 1];
  postData.toCharArray(Buf, postData.length() + 1);
  Serial.println(Buf);
}

void envioInformacion() {
  byte status = pinWrapper(serverName,&sendSDtoServer);
}

void unionInicializacionWifiSD() {
  Serial.println("Inicializando wifi | sd ...");
  bool init_sd = sdInicializacion(id_device, ssid, password, serverName);
  bool init_wifi = wifiInicializacion(ssid, password);
  Serial.println(init_sd ? "si sd" : "no sd");
  Serial.println(init_wifi ? "si wifi" : "no wifi");

  if (!init_sd && !init_wifi) {  //verificar si el wifi o el sd funciona, se admite que uno funcione y el otro no
    ESP.restart();
    //La unica posibilidad para reiniciar el dispoditivo es que ni el wifi ni el SD funcionen
  }
}