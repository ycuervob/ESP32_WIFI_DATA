#include <Arduino.h>
#include "dataTypes.h"

//Definicion de estados para luego mostrar por el serial
#ifndef BAD_DATA
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

void setup();
void defineSerial();
void printFromSerial(String);
void almacenamientoDatos();
void pinesyvariables();
void EncenderDispositivos();
void ApagarDispositivos();
void gpsInicialization();
void tempInicialization();
void initWIFI();
void initSD();
void printStatusGeneral(byte);
void printStatusSDtoWIFI(byte);
void getLine(String &, int *);
void setLine(int *);
void getLine(String &, String *);
void endSD();
bool acelerometroAlto(int);
void timeWrapper(unsigned long, void (*)());
void timeWrapper(unsigned long, int, bool (*)(int));
void timeWrapper(unsigned long, byte (*)());
void acelerometro(acelerometroDataType &);
void gpsDatos(gpsDataType &);
void initGlobalVar();
void getVariables(globVars &,  String *);
void tempyhumedad(temyhumDataType &);
int minAcelerometro();

bool saveDataSD(String);
bool acelerometroInicializacion();
bool sdInicializacion();
bool wifiInicializacion(const char *, const char *);

int tiempoEnvio(int);
int tiempoLectura();
int tiempoEspera();
int tiempoEsperaWifi();
int tiempoConexionWifi();

byte envioInformacion();
byte httpmyRequest(String, const char *);
byte pinWrapper(byte (*)());
byte pinWrapper(String, byte (*)(String));
byte pinWrapper(const char *, const char *, const char *, byte (*)(const char *, const char *, const char *));
byte sendSDtoServer(const char *, const char *, const char *);
byte readLine(String *, int *);
byte guardaDatosSD(String);
String createPostData(paqueteDataType &);
#endif