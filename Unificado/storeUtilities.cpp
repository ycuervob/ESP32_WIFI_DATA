#include <Arduino.h>
#include "utilities.h"

String createPostData(struct paqueteDataType &postData) {
  if (postData.gpsDatos.flon == String("0.000000") || postData.gpsDatos.flat == String("0.000000")) {
    return "NULL";  // No envia datos donde el gps no esté funcionando o alun dato esté mal
  }

  String str_postData = String("{ \"lista\":[") + "\""
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

byte guardaDatosGeneral(String postData) {
  if(postData == "NULL"){
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
/* POR IMPLEMENTAR
bool sendSDtoServer(){

}
*/
