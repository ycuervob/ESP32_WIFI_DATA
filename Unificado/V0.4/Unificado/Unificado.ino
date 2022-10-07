#include "utilities.h"
const int pinBateria = 35;
byte x = 1;
byte y = 1;

// Data from the device
const String id_device = "dispositivo_prueba";
int bateria = 0;
void ProcesamientoDeInformacion() {

  String *array_tempyhym = tempyhumedad();
  String *array_gpsDatos = gpsDatos();
  double *array_acelerometro = acelerometro();
  bateria = analogRead(pinBateria);
  httpmyRequest(
    id_device,
    String(bateria),
    array_tempyhym[0],
    array_tempyhym[1],
    array_gpsDatos[0],
    array_gpsDatos[1],
    array_gpsDatos[2],
    array_gpsDatos[3],
    array_gpsDatos[4],
    array_acelerometro[0],
    array_acelerometro[1],
    array_acelerometro[2],
    array_acelerometro[3]);
  delete[] array_gpsDatos;
  delete[] array_acelerometro;
  delete[] array_tempyhym;
}


void setup() {
  gpsInicialization();
  wifiInicializacion();
  tempInicialization();
  acelerometroInicializacion();
  pinesyvariables();
  EncenderDispositivos();
  sdInitialization();

  // falta implemetnar código para que despues de iniciarlizar SD, si hay, suba los existentes si puede
}

void loop() {
  // Control de encendido
  EncenderDispositivos();
  sdInitialization();
  while (x <= 15) {                // Mientras x sea menor o igual a 5 ejecuto las instrucciones
    ProcesamientoDeInformacion();  // Procesamiento de información
    x = x + 1;                     // Incrementa en uno el valor de x
  }
  x = 0;
  ApagarDispositivos();
  /*while(y <= 2000 ){
    if(acelerometroAlto()== true) break;
    delay(10);
    y=y+1;    
  }
  y=0;*/
  delay(5000);
}