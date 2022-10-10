#include <Arduino.h>
#include "dataTypes.h"

void setup();
void defineSerial();
void printFromSerial(String);
void ProcesamientoDeInformacion();
void gpsInicialization();
void tempInicialization();
void pinesyvariables();
void EncenderDispositivos();
void ApagarDispositivos();
bool acelerometroInicializacion();
bool saveDataSD(String);
bool sdInitialization();
bool wifiInicializacion();
bool acelerometroAlto();
bool httpmyRequest(String);
acelerometroDataType acelerometro();
gpsDataType gpsDatos();
temyhumDataType tempyhumedad();
bool guardaDatosGeneral(struct paqueteDataType &postData);
String createPostData(struct paqueteDataType &postData);


