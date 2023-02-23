#include "generalUtilities.h"
#include "storeUtilities.h"
#include "../variablesGlobalesUtilities.h"
#include "../dataTypes.h"
#include "../control/wrappers.h"
#include "../componentes/gpsUtilities.h"
#include "../componentes/tempUtilities.h"
#include "../componentes/acelerometroUtilities.h"
#include "../componentes/termocuplaUtilities.h"
#include "../componentes/wifiUtilities.h"
#include "../componentes/sdUtilities.h"

// Variables globales para el manejo de la bateria.
const int pinBateria = 35;
byte x = 1;
byte y = 1;
int bateria = 0;

// funciones de almacenamiento ----------------------------------

/**
 * @brief Crea un dato sipo paqueteDataType con los datos de los sensores y lo almacena en la micro sd.
 * Si no hay micro sd, se reintenta conectar a la micro sd hasta que se conecte o se pase el tiempo de 5 segundos.
 * Si no se puede conectar a la micro sd, se descartan los datos.
 */
void almacenamientoDatos()
{
  globVars gVars = getGlobalVar();
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
  while (status == NOT_SD)
  {
    endSD();
    sdInicializacion();
    status = pinWrapper(postData, &guardaDatosSD);
    if (millis() - start > 5000)
    {
      break;
    }
  }

  char *estados_general[4] = {"Datos erroneos, descartados", "No hay SD datos descartados", "Almacenado"};
  Serial.println(estados_general[status]);
  char Buf[postData.length() + 1];
  postData.toCharArray(Buf, postData.length() + 1);
  Serial.println(Buf);
}

/**
 * @brief Función que envia los datos de la micro sd al servidor retorna el estado del envio.
 *
 * @return byte | ARCHIVO_NO_ABIERTO 0 1 | LEIDO 1 | NO_MAS_DATOS 2 | LEIDO_PERO_NO_ENVIADO 3
 */
byte envioInformacion()
{
  globVars gVars = getGlobalVar();
  byte status = pinWrapper(gVars.server.c_str(), &sendSDtoServer);
  char *estados_general[7] = {"ARCHIVO_NO_ABIERTO", "LEIDO", "NO_MAS_DATOS", "LEIDO_PERO_NO_ENVIADO", "FALLO_AL_ENVIAR", "ENVIADO", "NO_WIFI"};
  Serial.println(estados_general[status]);
  return status;
}
