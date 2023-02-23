#include <Arduino.h>
#include <HardwareSerial.h>
#include <SPI.h>

//Definicion de pines
int pinSD = 14;
int pinTem = 13;
int pinGps = 12;
int pinUsb = 27;
int pinTermo = 26;
int status_sd = 25; //Se define para saber el estado de la microsd
int status_wifi = 33; //Se define para saber el estado del wifi
int status_enviado = 32; //Se define para saber si se esta enviando datos

/**
 * @brief Funcion que inicializa los pines de los dispositivos.
 * 
 */
void pinesyvariables() {
  pinMode(2, OUTPUT);
  pinMode(pinSD, OUTPUT);
  pinMode(pinTem, OUTPUT);
  pinMode(pinGps, OUTPUT);
  pinMode(pinUsb, OUTPUT);
  pinMode(pinTermo, OUTPUT);
  pinMode(status_sd, OUTPUT);
  pinMode(status_wifi, OUTPUT);
  pinMode(status_enviado, OUTPUT);
}

void encenderLed(char led, bool estado) {
  switch (led)
  {
  case 's':
    digitalWrite(status_sd, estado ? HIGH : LOW);
    break;
  case 'w':
    digitalWrite(status_wifi, estado ? HIGH : LOW);
    break;
  case 'e':
    digitalWrite(status_enviado, estado ? HIGH : LOW);
    break;
  default:
    break;
  }
  
}

/**
 * @brief Funcion que enciende los dispositivos.
 * 
 */
void EncenderDispositivos() {
  digitalWrite(pinSD, HIGH);
  digitalWrite(pinTem, HIGH);
  digitalWrite(pinGps, HIGH);
  digitalWrite(pinUsb, HIGH);
  digitalWrite(pinTermo, HIGH);
}

/**
 * @brief Funcion que apaga los dispositivos.
 * 
 */
void ApagarDispositivos() {
  digitalWrite(pinSD, LOW);
  digitalWrite(pinTem, LOW);
  digitalWrite(pinGps, LOW);
  digitalWrite(pinUsb, LOW);
  digitalWrite(pinTermo, LOW);
}