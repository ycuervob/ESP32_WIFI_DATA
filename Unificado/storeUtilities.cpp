#include <Arduino.h>
#include "utilities.h"

String createPostData(struct paqueteDataType &postData) {
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

bool guardaDatosGeneral(struct paqueteDataType &postData) {
  if (postData.gpsDatos.flon == String("0.000000") || postData.gpsDatos.flat == String("0.000000")) {
    return false;  // No envia datos donde el gps no esté funcionando o alun dato esté mal
  }
  
  String str_postData = createPostData(postData);
  printFromSerial(str_postData); //Se puede comentar y descomentar esta linea para evitar estar comentando todo

  if (!httpmyRequest(str_postData)) {
    if (!saveDataSD(str_postData)) {
      return false;
    }
  }

  return true;
}