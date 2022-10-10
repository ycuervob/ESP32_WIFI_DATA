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
  bool data_enviada = guardaDatosGeneral(dataToPost);
  free(&dataToPost);
}


void setup() {
  gpsInicialization();
  tempInicialization();
  acelerometroInicializacion();
  pinesyvariables();
  EncenderDispositivos();
  //Aqui debe haber un delay, ya que el dispositivo wifi se dera en prender y en estár disponible
  bool init_sd = sdInitialization();
  bool init_wifi = wifiInicializacion();
  if (!init_sd && !init_wifi) {  //verificar si el wifi o el sd funciona, se admite que uno funcione y el otro no
    ESP.restart();               //La unica posibilidad para reiniciar el dispoditivo es que ni el wifi ni el SD funcionen
  }

  // falta implemetnar código para que despues de iniciarlizar SD, si hay, suba los existentes si puede
}

void loop() {
  EncenderDispositivos();
  sdInitialization();
  wifiInicializacion();
  while (x <= 15) {               
    ProcesamientoDeInformacion();  
    x = x + 1;                     
  }
  x = 0;
  ApagarDispositivos();
  /*
  while(y <= 2000 ){
    if(acelerometroAlto()== true) break;
    delay(10);
    y=y+1;    
  }
  y=0;
  */
  delay(15000);
}