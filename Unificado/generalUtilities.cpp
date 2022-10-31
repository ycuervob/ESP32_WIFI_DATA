#include <Arduino.h>
#include "utilities.h"
#include "wrappers.h"

const int pinBateria = 35;
byte x = 1;
byte y = 1;
const String id_device = "dispositivo_prueba";
int bateria = 0;

void almacenamientoDatos() {
  paqueteDataType dataToPost;
  tempyhumedad(dataToPost.temyhDatos);
  gpsDatos(dataToPost.gpsDatos);
  acelerometro(dataToPost.acelerometroDatos);
  dataToPost.bateria = analogRead(pinBateria);
  dataToPost.id_device = id_device;

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

  char* estados_general[4] = { "Datos erroneos, descartados", "Fallo al enviar al servidor, guardado en SD", "No hay wifi ni SD --", "Enviado al servidor" };
  Serial.println(estados_general[status]);
  char Buf[postData.length() + 1];
  postData.toCharArray(Buf, postData.length() + 1);
  Serial.println(Buf);
}

void envioInformacion() {
  byte status = pinWrapper(&sendSDtoServer);
}

void unionInicializacionWifiSD() {
  Serial.println("Inicializando wifi | sd ...");
  bool init_wifi = wifiInicializacion();
  bool init_sd = sdInicializacion();
  Serial.println(init_sd ? "si sd" : "no sd");
  Serial.println(init_wifi ? "si wifi" : "no wifi");

  if (!init_sd && !init_wifi) {  //verificar si el wifi o el sd funciona, se admite que uno funcione y el otro no
    ESP.restart();
    //La unica posibilidad para reiniciar el dispoditivo es que ni el wifi ni el SD funcionen
  }
}