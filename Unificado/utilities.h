#include <Arduino.h>
#include "dataTypes.h"

//Definicion de estados para luego mostrar por el serial
#ifndef BAD_DATA
//Para manejo de envio normal de datos
#define BAD_DATA 0
#define NOT_WIFI_STORED 1
#define NOT_WIFI_NOT_SD 2
#define SENT 3
//Para enviar datos de SD por HTTP
#define ARCHIVO_NO_ABIERTO 0
#define LEIDO 1
#define NO_MAS_DATOS 2
#define LEIDO_PERO_NO_ENVIADO 3
#endif

void setup();
void defineSerial();
void printFromSerial(String);
void ProcesamientoDeInformacion();
void pinesyvariables();
void EncenderDispositivos();
void ApagarDispositivos();
void gpsInicialization();
void tempInicialization();
void unionInicializacionWifiSD(byte);
void printStatusGeneral(byte);
void printStatusSDtoWIFI(byte);
void getLine(int *);
void setLine(int *);

bool saveDataSD(String);
bool acelerometroInicializacion();
bool sdInicializacion();
bool wifiInicializacion();
bool acelerometroAlto();
bool httpmyRequest(String);

byte sendSDtoServer();
byte readLine(String*, int*);
void acelerometro(acelerometroDataType &);
void gpsDatos(gpsDataType &);
void tempyhumedad(temyhumDataType &);
byte guardaDatosGeneral(String);
String createPostData(paqueteDataType &);

