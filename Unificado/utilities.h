#include <Arduino.h>
#include "dataTypes.h"

//Definicion de estados para luego mostrar por el serial
#ifndef BAD_DATA
//Para manejo de envio normal de datos
#define BAD_DATA 0
#define NOT_SD 1
#define STORED 2
//Para enviar datos de SD por HTTP
#define ARCHIVO_NO_ABIERTO 0
#define LEIDO 1
#define NO_MAS_DATOS 2
#define LEIDO_PERO_NO_ENVIADO 3

void setup();
void defineSerial();
void printFromSerial(String);
void almacenamientoDatos();
void pinesyvariables();
void EncenderDispositivos();
void ApagarDispositivos();
void gpsInicialization();
void tempInicialization();
void unionInicializacionWifiSD();
void printStatusGeneral(byte);
void printStatusSDtoWIFI(byte);
void getLine(int *);
void setLine(int *);
void endSD();
void acelerometroAlto();
void timeWrapper(unsigned long, void (*)());
void timeWrapper(unsigned long, bool (*)());
void acelerometro(acelerometroDataType &);
void gpsDatos(gpsDataType &);
void tempyhumedad(temyhumDataType &);
void endSD();
void envioInformacion();

bool saveDataSD(String);
bool acelerometroInicializacion();
bool sdInicializacion(const char *, const char *, const char *, const char *);
bool wifiInicializacion(const char *, const char *);
bool httpmyRequest(String, const char *);

byte pinWrapper(byte (*)());
byte pinWrapper(String, byte (*)(String));
byte pinWrapper(const char *, byte (*)(const char *));
byte sendSDtoServer(const char *);
byte readLine(String *, int *);
byte guardaDatosSD(String);
String createPostData(paqueteDataType &);

#endif