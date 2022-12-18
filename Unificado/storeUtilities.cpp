#include <Arduino.h>
#include "utilities.h"

/**
  Retorna un String con el formato para enviar por medio de HTTP y admitido por el servidor
*/
String createPostData(struct paqueteDataType &postData) {
  if (postData.gpsDatos.flon == String("0.0") || postData.gpsDatos.flat == String("0.0")) {
    return "NULL";  // No envia datos donde el gps no esté funcionando o alun dato esté mal
  }

  String str_postData = String("{\"lista\":[") + "\""
                        + postData.id_device + "\","
                        + postData.bateria + ","
                        + postData.temyhDatos.temperatura + ","
                        + postData.temyhDatos.humedad + ","
                        + postData.gpsDatos.flat + ","
                        + postData.gpsDatos.flon + "," + "\""
                        + postData.gpsDatos.timestamp + "\","
                        + postData.gpsDatos.numero_satelites + ","
                        + postData.gpsDatos.varianza + ","
                        + String(postData.gpsDatos.velocidad) + ","
                        + postData.acelerometroDatos.x + ","
                        + postData.acelerometroDatos.y + ","
                        + postData.acelerometroDatos.z + ","
                        + postData.acelerometroDatos.total + "]}";

  return str_postData;
}

void getVariables(struct globVars &gVars, String *nFiles) {
  getLine(nFiles[0], &gVars.device);
  getLine(nFiles[1], &gVars.ssid);
  getLine(nFiles[2], &gVars.pass);
  getLine(nFiles[3], &gVars.server);
  getLine(nFiles[4], &gVars.time_max);
  getLine(nFiles[5], &gVars.vel_max);
  getLine(nFiles[6], &gVars.vel_min);
  getLine(nFiles[7], &gVars.tiempo_lectura);
  getLine(nFiles[8], &gVars.max_tiempo_enviado);
  getLine(nFiles[9], &gVars.porcentaje_enviado);
  getLine(nFiles[10], &gVars.min_acelerometro_anormal);
}


/**
  Retorna los siguientes estados:
  - BAD_DATA 0 : Se recolecto datos de gps en mal estado y por tanto el paquete no sirve  
  - NOT_SD 1   : Hubo elgún error al guardar en la SD
  - STORED 2   : El dato se almacenó correctamente
*/
byte guardaDatosSD(String postData) {
  if (postData == "NULL") {
    return BAD_DATA;
  }

  if (!saveDataSD(postData)) {
    return NOT_SD;
  }

  return STORED;
}


/**
  Lee todos los datos de la micro sd y los va enviando al servidor uno por uno.
  Si algún dato falla entonces descartará el dato y seguirá en el próximo reinicio o próxima vez que se llame la función.
  También si en medio del proceso algún dato no se puede enviar entonces descartará el dato y continuará la proxima vez que se reinicie o que se llame la función.
  Estados:
    - ARCHIVO_NO_ABIERTO 0
    - LEIDO 1
    - NO_MAS_DATOS 2
    - LEIDO_PERO_NO_ENVIADO 3

*/

//Posición actual que se está leyendo en la micro sd, en bytes.
int currPos;
byte sendSDtoServer(const char *serverName, const char *ssid, const char *password) {
  String currLine = "";
  String lineFile = "/currentLine.txt";
  getLine(lineFile, &currPos);
  byte status = readLine(&currLine, &currPos);

  switch (status) {
    case ARCHIVO_NO_ABIERTO:
      endSD();
      sdInicializacion();
      break;
    case LEIDO:
      {
        unsigned long start = millis();
        switch (httpmyRequest(currLine, serverName)) {
          case FALLO_AL_ENVIAR:
            {
              status = ENVIADO;
              while (httpmyRequest(currLine, serverName) == FALLO_AL_ENVIAR) {
                if (millis() - start > 5000) {
                  status = LEIDO_PERO_NO_ENVIADO;
                  setLine(&currPos);
                  break;
                }
              }
            }
            break;
          case ENVIADO:
            setLine(&currPos);
            status = ENVIADO;
            break;
          case NO_WIFI:
            wifiInicializacion(ssid, password);
            status = NO_WIFI;
            break;
          default:
            break;
        }
      }
      break;
    case NO_MAS_DATOS:
      break;
    default:
      status = LEIDO_PERO_NO_ENVIADO;
      break;
  }

  return status;
}