#include <Arduino.h>
#include <HardwareSerial.h>
#include <SPI.h>

// Control de encencido
int pinSD = 14;
int pinTem = 13;
int pinGps = 12;
int pinUsb = 27;

byte pinWrapper(byte (*func)()) {
  digitalWrite(2, HIGH);
  byte status = func();
  digitalWrite(2, LOW);
  return status;
}

byte pinWrapper(String data, byte (*func)(String)) {
  digitalWrite(2, HIGH);
  byte status = func(data);
  digitalWrite(2, LOW);
  return status;
}

void pinesyvariables() {
  pinMode(2, OUTPUT);
  pinMode(pinSD, OUTPUT);
  pinMode(pinTem, OUTPUT);
  pinMode(pinGps, OUTPUT);
  pinMode(pinUsb, OUTPUT);
}

void EncenderDispositivos() {
  digitalWrite(pinSD, HIGH);
  digitalWrite(pinTem, HIGH);
  digitalWrite(pinGps, HIGH);
  digitalWrite(pinUsb, HIGH);
}

void ApagarDispositivos() {
  digitalWrite(pinSD, LOW);
  digitalWrite(pinTem, LOW);
  digitalWrite(pinGps, LOW);
  digitalWrite(pinUsb, LOW);
}