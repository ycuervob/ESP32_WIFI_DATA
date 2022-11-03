#include <Arduino.h>


void timeWrapper(unsigned long time, void (*func)()) {
  for (unsigned long start = millis(); millis() - start < time;) {
    func();
  }
}

void timeWrapper(unsigned long time, byte (*func)()) {
  for (unsigned long start = millis(); millis() - start < time;) {
    if(func() == 2){//NO MAS DATOS
      return;
    }
  }
}

void timeWrapper(unsigned long time, bool (*func)()) {
  for (unsigned long start = millis(); millis() - start < time;) {
    bool mybool = func();
    if (mybool) {
      return;
    }
  }
}

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

byte pinWrapper(const char *data, const char *data1, const char *data2, byte (*func)(const char *, const char *, const char *)) {
  digitalWrite(2, HIGH);
  byte status = func(data, data1, data2);
  digitalWrite(2, LOW);
  delay(200);
  return status;
}