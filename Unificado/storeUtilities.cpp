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
                        + postData.acelerometroDatos.x + ","
                        + postData.acelerometroDatos.y + ","
                        + postData.acelerometroDatos.z + ","
                        + postData.acelerometroDatos.total + "]}";

  return str_postData;
}


/**
  Recibe datos en el formato para guardar en la bd.
  Retorna los siguientes estados:
  - BAD_DATA 0          : Se recolecto datos de gps en mal estado y por tanto el paquete no sirve  
  - NOT_WIFI_STORED 1   : No hubo internet a la hora de guardar el dato por tanto se almacena en la SD
  - NOT_WIFI_NOT_SD 2   : No sirvió ni el internet ni la micro SD por tanto el dispositivo debe reiniciarse
  - SENT 3              : Se envió el dato correctamente
*/
byte guardaDatosGeneral(String postData) {
  if (postData == "NULL") {
    return BAD_DATA;
  }

  byte status = SENT;
  if (!httpmyRequest(postData)) {
    status = NOT_WIFI_STORED;
    if (!saveDataSD(postData)) {
      return NOT_WIFI_NOT_SD;
    }
  }

  return status;
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
byte sendSDtoServer() {
  String currLine = "";

  getLine(&currPos);
  byte status = readLine(&currLine, &currPos);
  while (status == LEIDO) {
    if (!httpmyRequest(currLine)) {
      status = LEIDO_PERO_NO_ENVIADO;
      break;
    };
    status = readLine(&currLine, &currPos);
  }

  return status;
}