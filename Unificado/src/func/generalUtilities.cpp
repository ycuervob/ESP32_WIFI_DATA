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
#include "../componentes/pinnesUtilities.h"

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
  paqueteDataType dataToPost;
  tempyhumedad(dataToPost.temyhDatos);
  gpsDatos(dataToPost.gpsDatos);
  acelerometro(dataToPost.acelerometroDatos);
  termocupla(dataToPost.termocuplaDatos);
  setVelocidad(dataToPost.gpsDatos.velocidad);
  dataToPost.bateria = analogRead(pinBateria);
  dataToPost.id_device = getGlobalVar().device;
  dataToPost.id_grupo_lectura = getGlobalVar().id_grupo_lectura;
  String postData = createPostData(dataToPost);
  byte status = guardaDatosSD(postData);

  unsigned long start = millis();
  while (status == NOT_SD)
  {
    endSD();
    sdInicializacion();
    status = guardaDatosSD(postData);
    if (millis() - start > 5000)
    {
      break;
    }
  }

  /*
  char *estados_general[4] = {"Datos erroneos, descartados", "No hay SD datos descartados", "Almacenado"};
  Serial.println(estados_general[status]);
  char Buf[postData.length() + 1];
  postData.toCharArray(Buf, postData.length() + 1);
  Serial.println(Buf);
  */

  if (status == STORED)
  {
    encenderLed('c', true);
    delay(100);
    encenderLed('c', false);
  }
}

/**
 * @brief Función que envia los datos de la micro sd al servidor retorna el estado del envio.
 *
 * @return byte | ARCHIVO_NO_ABIERTO 0 1 | LEIDO 1 | NO_MAS_DATOS 2 | LEIDO_PERO_NO_ENVIADO 3
 */
byte envioInformacion()
{
  if (getGlobalVar().id_grupo_lectura == 0)
  {
    initGrupoLectura();
  }
  
  byte status = sendSDtoServer();
  if (status == 5)
  {
    encenderLed('e', true);
    delay(100);
    encenderLed('e', false);
  }
  /*
  char *estados_general[7] = {"ARCHIVO_NO_ABIERTO", "LEIDO", "NO_MAS_DATOS", "LEIDO_PERO_NO_ENVIADO", "FALLO_AL_ENVIAR", "ENVIADO", "NO_WIFI"};
  Serial.println(estados_general[status]);
  */
  return status;
}
