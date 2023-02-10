#include <Arduino.h>
#include <HardwareSerial.h>
#include <SPI.h>

//Definicion de pines
int pinSD = 14;
int pinTem = 13;
int pinGps = 12;
int pinUsb = 27;
int pinTermo = 26;

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