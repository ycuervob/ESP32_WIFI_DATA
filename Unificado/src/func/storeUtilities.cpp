#include <Arduino.h>
#include "../componentes/sdUtilities.h"
#include "../componentes/wifiUtilities.h"
#include "../componentes/dataTypes.h"
#include "storeUtilities.h"


//Variable global con la Posición actual que se está leyendo en la micro sd, en bytes.
int currPos;

/**
 * @brief Recibe los datos recogidos por los sensores y los formatea para ser enviados al servidor
 * 
 * @param postData paqueteDataType | ver dataTypes.h
 * @return String | Datos formateados para ser enviados al servidor
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
                        + postData.acelerometroDatos.total + ","
                        + postData.termocuplaDatos.temp + "]}";

  return str_postData;
}

/**
 * @brief Recibe la estructura de datos que almacena las variables globales y un arreglo de strings con los nombres de los archivos de las respectivas variables
 * guarda los datos de la microsd en la estructura de datos.
 *
 * @param postData paqueteDataType | ver dataTypes.h
 */
void getVariables(struct globVars &gVars, String *nFiles) {
  getLine(nFiles[0], &gVars.device);
  getLine(nFiles[1], &gVars.ssid);
  getLine(nFiles[2], &gVars.pass);
  getLine(nFiles[3], &gVars.server);
  getLine(nFiles[4], &gVars.tiempo_max);
  getLine(nFiles[5], &gVars.vel_no_reposo);
  getLine(nFiles[6], &gVars.vel_reposo_max);
  getLine(nFiles[7], &gVars.tiempo_lectura_guardado);
  getLine(nFiles[8], &gVars.min_tiempo_enviado);
  getLine(nFiles[9], &gVars.porcentaje_enviado);
  getLine(nFiles[10], &gVars.acelerometro_anormal);
  getLine(nFiles[11], &gVars.tiempo_epera_conexion);
  getLine(nFiles[12], &gVars.tiempo_conexion_wifi);
}


/**

*/

/**
 * @brief   Retorna los siguientes estados:
  - BAD_DATA 0 : Se recolecto datos de gps en mal estado y por tanto el paquete no sirve  
  - NOT_SD 1   : Hubo elgún error al guardar en la SD
  - STORED 2   : El dato se almacenó correctamente
 * 
 * @param postData 
 * @return byte 
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
 * @brief   Lee todos los datos de la micro sd y los va enviando al servidor uno por uno.
  Si algún dato falla entonces descartará el dato y seguirá en el próximo reinicio o próxima vez que se llame la función.
  También si en medio del proceso algún dato no se puede enviar entonces descartará el dato y continuará la proxima vez que se reinicie o que se llame la función.
  Estados:
    - ARCHIVO_NO_ABIERTO 0
    - LEIDO 1
    - NO_MAS_DATOS 2
    - LEIDO_PERO_NO_ENVIADO 3
 * 
 * @param serverName ip o url del servidor
 * @param ssid nombre de la red wifi
 * @param password password de la red wifi
 * @return byte 
 */
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