#include <Arduino.h>
#include "dataTypes.h"

//Definicion de estados para luego mostrar por el serial
#ifndef BAD_DATA
#define BAD_DATA 0
#define NOT_WIFI_STORED 1
#define NOT_WIFI_NOT_SD 2
#define SENT 3
#endif

void setup();
void defineSerial();
void printFromSerial(String);
void ProcesamientoDeInformacion();
void pinesyvariables();
void EncenderDispositivos();
void ApagarDispositivos();
bool saveDataSD(String);
void gpsInicialization();
void tempInicialization();
bool acelerometroInicializacion();
bool sdInicializacion();
bool wifiInicializacion();
bool acelerometroAlto();
bool httpmyRequest(String);
acelerometroDataType acelerometro();
gpsDataType gpsDatos();
temyhumDataType tempyhumedad();
byte guardaDatosGeneral(String);
String createPostData(struct paqueteDataType &postData);


