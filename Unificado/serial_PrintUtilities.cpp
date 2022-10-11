#include <Arduino.h>
bool serial_inincialized = false;
char* estados_general[4] = { "Datos erroneos, descartados", "No wifi, guardado en SD", "No hay wifi ni SD --", "Enviado al servidor" };
char* estados_SDtoWIFI[4] = { "Archivo no abierto, se descarta dato", "Leido", "No hay mas datos en la SD", "El dato fue leido pero no enviado, se descarta" };

/**
  Define el serial si no está definido, esto con el fin de evitar algún error
  Si no se llama está función primero no se podrá usar @printFromSerial
*/
bool defineSerial() {
  if (!serial_inincialized) {
    Serial.begin(115200);
    serial_inincialized = true;
  }
}

void printStatusGeneral(byte status) {
  defineSerial();
  Serial.print("Estado del dato: ");
  Serial.println(estados_general[status]);
}

void printStatusSDtoWIFI(byte status) {
  defineSerial();
  Serial.print("Estado del dato: ");
  Serial.println(estados_SDtoWIFI[status]);
}

/**
  Función que se pude usar para modelar los Serial.println de una mejor forma.
*/
void printFromSerial(String postData) {
  defineSerial();
  Serial.println(F("id_device_in\t bateria\t temperatura\t humedad\t flat\t flon\t timestamp\t numero_satelites\t varianza\t x\t y\t z\t total"));
  Serial.println(postData);
}