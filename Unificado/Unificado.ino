#include <Arduino.h>
#include "utilities.h"

const int pinBateria = 35;
byte x = 1;
byte y = 1;

// Data from the device
const String id_device = "dispositivo_prueba";
int bateria = 0;

void ProcesamientoDeInformacion() {
  paqueteDataType dataToPost;
  dataToPost.temyhDatos = tempyhumedad();
  dataToPost.gpsDatos = gpsDatos();
  dataToPost.acelerometroDatos = acelerometro();
  dataToPost.bateria = analogRead(pinBateria);
  dataToPost.id_device = id_device;
  String postData = createPostData(dataToPost);
  byte status = guardaDatosGeneral(postData);
  //printFromSerial(postData, status); //Se puede comentar y descomentar para que muestre logs
  free(&dataToPost);
}

/**
  Se puede comprobar si alguna inicializacion es fallida porque retornan bool:
    EVITAR ESCRIBIR Serial.print o cualquier variante pues si se activa el serial el ESP32 silo funciona con PC
    Usar Serial.print solo para probar y luego eliminarlo.
*/
void setup() {
  gpsInicialization();
  tempInicialization();
  acelerometroInicializacion();
  pinesyvariables();
  EncenderDispositivos();
  //Aqui debe haber un delay, ya que el dispositivo wifi se dera en prender y en estár disponible
  bool init_sd = sdInicializacion();
  bool init_wifi = wifiInicializacion();
  if (!init_sd && !init_wifi) {  //verificar si el wifi o el sd funciona, se admite que uno funcione y el otro no
    ESP.restart();               //La unica posibilidad para reiniciar el dispoditivo es que ni el wifi ni el SD funcionen
  }

  // falta implemetnar código para que despues de iniciarlizar SD, si hay, suba los existentes si puede
}

void loop() {
  EncenderDispositivos();
  sdInicializacion();
  //delay(30000); //Este delay es necesario porque el modem wifi puede demorarse en encender si no se está usando entonces dejarlo comentado
  wifiInicializacion();
  while (x <= 15) {  //Mejor numero de veces que tiempo, ya que en varias funciones como la del gps o la del Wifi, se pueden presentar delays.
    ProcesamientoDeInformacion();
    x += 1;
  }
  x = 0;
  ApagarDispositivos();
  /*
  for(unsigned long start = millis(); millis() - start < 15000;){
    if(acelerometroAlto()== true) break;
    delay(10);
    y=y+1;    
  }
  y=0;
  */
  delay(15000);
}