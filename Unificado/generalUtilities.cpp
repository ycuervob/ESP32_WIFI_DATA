#include <Arduino.h>
#include "utilities.h"

const int pinBateria = 35;
byte x = 1;
byte y = 1;
const String id_device = "dispositivo_prueba";
int bateria = 0;

void timeWrapper(unsigned long time, void (*func)()) {
  for (unsigned long start = millis(); millis() - start < time;) {
    func();
  }
}

void timeWrapper(unsigned long time, bool (*func)()) {
  for (unsigned long start = millis(); millis() - start < time;) {
    if (func()) {
      break;
    }
  }
}

void ProcesamientoDeInformacion() {
  paqueteDataType dataToPost;
  tempyhumedad(dataToPost.temyhDatos);
  gpsDatos(dataToPost.gpsDatos);
  acelerometro(dataToPost.acelerometroDatos);
  dataToPost.bateria = analogRead(pinBateria);
  dataToPost.id_device = id_device;

  String postData = createPostData(dataToPost);
  byte status = pinWrapper(postData, &guardaDatosGeneral);

  //char* estados_general[4] = { "Datos erroneos, descartados", "Fallo al enviar al servidor, guardado en SD", "No hay wifi ni SD --", "Enviado al servidor" };
  //Serial.println(estados_general[status]);
  //char Buf[postData.length() + 1];
  //postData.toCharArray(Buf, postData.length() + 1);
  //Serial.println(Buf);

  if (status == NOT_WIFI_NOT_SD) {
    endSD();
    sdInicializacion();
  }
}

void unionInicializacionWifiSD() {
  //Serial.println("Inicializando wifi | sd ...");
  bool init_wifi = wifiInicializacion();
  bool init_sd = sdInicializacion();
  //Serial.println(init_sd ? "si sd" : "no sd");
  //println(init_wifi ? "si wifi" : "no wifi");

  if (!init_sd && !init_wifi) {  //verificar si el wifi o el sd funciona, se admite que uno funcione y el otro no
    endSD();
    if (!sdInicializacion()) {
      ESP.restart();
    }
    //La unica posibilidad para reiniciar el dispoditivo es que ni el wifi ni el SD funcionen
  }

  if (init_wifi && init_sd) {
    byte status = pinWrapper(&sendSDtoServer);
  }
}