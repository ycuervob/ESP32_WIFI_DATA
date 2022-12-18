#include <Arduino.h>
#include "utilities.h"
#include "wrappers.h"

const int pinBateria = 35;
byte x = 1;
byte y = 1;
int bateria = 0;
globVars gVars;
globVars nFiles;
bool only_first_time = true;

int tiempoEspera() {
  if (gVars.velocidad == 0.0) {
    return 0;
  } else if (gVars.velocidad <= gVars.vel_min) {
    return gVars.time_max * 60000;
  } else if (gVars.velocidad > gVars.vel_min && gVars.velocidad <= gVars.vel_max) {
    return (gVars.time_max - (gVars.velocidad / (gVars.vel_max / 10))) * 60000;  //funcion de tiempo
  } else {
    return 0;
  }
}

int tiempoLectura() {
  return gVars.tiempo_lectura;
}

int minAcelerometro() {
  return gVars.min_acelerometro_anormal;
}

int tiempoEsperaWifi(){
  return gVars.tiempo_epera_conexion;
}

int tiempoConexionWifi(){
  return gVars.tiempo_conexion_wifi;
}

int tiempoEnvio(int tiempo_esp) {
  return (tiempo_esp / gVars.porcentaje_enviado) >= gVars.max_tiempo_enviado * 1000 ? (tiempo_esp / gVars.porcentaje_enviado) : 0;
}

void initGlobalVar() {
  if (only_first_time) {
    String files[13] = { "/device.txt", "/ssid.txt", "/pass.txt", "/server.txt", "/maxT.txt", "/maxV.txt", "/minV.txt", "/Tlectura.txt", "/Tenviado.txt", "/porEnviado.txt", "/max_acel.txt", "/tiempo_espera_wifi.txt", "/tiempo_conexion_wifi.txt" };
    getVariables(gVars, files);
    only_first_time = false;
  }
}

void almacenamientoDatos() {
  paqueteDataType dataToPost;
  tempyhumedad(dataToPost.temyhDatos);
  gpsDatos(dataToPost.gpsDatos);
  acelerometro(dataToPost.acelerometroDatos);
  termocupla(dataToPost.termocuplaDatos);
  gVars.velocidad = dataToPost.gpsDatos.velocidad;
  dataToPost.bateria = analogRead(pinBateria);
  dataToPost.id_device = gVars.device;
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

byte envioInformacion() {
  byte status = pinWrapper(gVars.server.c_str(), gVars.ssid.c_str(), gVars.pass.c_str(), &sendSDtoServer);
  char *estados_general[7] = { "ARCHIVO_NO_ABIERTO", "LEIDO", "NO_MAS_DATOS", "LEIDO_PERO_NO_ENVIADO", "FALLO_AL_ENVIAR", "ENVIADO", "NO_WIFI" };
  Serial.println(estados_general[status]);
  return status;
}

void initSD() {
  bool init_sd = sdInicializacion();
  Serial.println(init_sd ? "si sd" : "no sd");
}

void initWIFI() {
  bool init_wifi = wifiInicializacion(gVars.ssid.c_str(), gVars.pass.c_str());
  Serial.println(init_wifi ? "si wifi" : "no wifi");
}