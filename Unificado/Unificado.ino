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
  temyhumDataType dataTempYHum;
  acelerometroDataType dataAcel;
  gpsDataType dataGPS;

  tempyhumedad(dataTempYHum);
  gpsDatos(dataGPS);
  acelerometro(dataAcel);
    
  dataToPost.temyhDatos = dataTempYHum;
  dataToPost.gpsDatos = dataGPS;
  dataToPost.acelerometroDatos = dataAcel;
  dataToPost.bateria = analogRead(pinBateria);
  dataToPost.id_device = id_device;

  String postData = createPostData(dataToPost);
  byte status = guardaDatosGeneral(postData);
  if(status == NOT_WIFI_NOT_SD){
    ESP.restart();
  }
  //char Buf[postData.length()+1];
  //postData.toCharArray(Buf, postData.length()+1);
  //printStatusGeneral(status); //Se puede comentar y descomentar para mostrar el status de los datos guardados.
  //Serial.println(Buf);
}

/**
  Se puede comprobar si alguna inicializacion es fallida porque retornan bool:
    Usar Serial.println solo para probar y luego eliminarlo.
    Ver @sendSDtoServer para verificar los estados que retorna e imprimir por serial información acorde.
    Ver @printStatusSDtoWIFI para poder imprimir que retorna los datos de sendSDtoServer
    Se puede usar @currPos para saber si por el momento se ha leido algún dato de la micro sd.
    Evitar Usar Serial.println en su lugar implementar alguna función en serial_PrintUtilities para mostrar logs.
*/
void unionInicializacionWifiSD() {
  bool init_sd = sdInicializacion();
  bool init_wifi = wifiInicializacion();
  //Serial.println(init_sd ? "si sd":"no sd");
  //Serial.println(init_wifi ? "si wifi":"no wifi");
  if (!init_sd && !init_wifi) {  //verificar si el wifi o el sd funciona, se admite que uno funcione y el otro no
    ESP.restart();               //La unica posibilidad para reiniciar el dispoditivo es que ni el wifi ni el SD funcionen
  }

  if (init_wifi && init_sd) {
    byte status = sendSDtoServer();
    //printStatusSDtoWIFI(status); //Se puede comentar y descomentar para que muestre los estados que tuvo al enviar al servidor
  }
}

/**
  Se puede comprobar si alguna inicializacion es fallida porque retornan bool:
    Usar Serial.println solo para probar y luego eliminarlo.
*/
void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  gpsInicialization();
  tempInicialization();
  acelerometroInicializacion();
  pinesyvariables();
}

void loop() {
  EncenderDispositivos();
  //delay(50000);//Aqui debe haber un delay, ya que el dispositivo wifi (usb) se demora en prender y en estár disponible
  unionInicializacionWifiSD();
  digitalWrite(2, HIGH);
  while (x <= 30) { 
    ProcesamientoDeInformacion();
    x += 1;
  }
  digitalWrite(2, LOW);
  x = 0;
  //ApagarDispositivos();
  delay(300000);
}