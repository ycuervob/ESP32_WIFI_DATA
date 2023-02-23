#ifndef STORE_UTILITIES_H
#define STORE_UTILITIES_H

#include <Arduino.h>

//Para manejo de envio normal de datos
#define BAD_DATA 0
#define NOT_SD 1
#define STORED 2
//Para leer datos de la SD
#define ARCHIVO_NO_ABIERTO 0
#define LEIDO 1
#define NO_MAS_DATOS 2
#define LEIDO_PERO_NO_ENVIADO 3
//Para los estados al enviar al servidor
#define FALLO_AL_ENVIAR 4
#define ENVIADO 5
#define NO_WIFI 6

byte sendSDtoServer(const char *serverName);

byte guardaDatosSD(String postData);

byte httpmyRequest(String packet, const char *serverName);

String createPostData(struct paqueteDataType &postData);

void getVariables(struct globVars &gVars, String *nFiles);

#endif //UTILITIES_H