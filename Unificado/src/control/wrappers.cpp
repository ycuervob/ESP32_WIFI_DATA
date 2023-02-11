#include <Arduino.h>

/**
 * @brief Wrapper que ejecuta una funcion por un tiempo determinado.
 * 
 * @param time 
 * @param func 
 */
void timeWrapper(unsigned long time, void (*func)()) {
  for (unsigned long start = millis(); millis() - start < time;) {
    func();
  }
}

/**
 * @brief Wrapper que ejecuta una funcion por un tiempo determinado.
 * 
 * @param time 
 * @param func byte 2: NO MAS DATOS
 */
void timeWrapper(unsigned long time, byte (*func)()) {
  for (unsigned long start = millis(); millis() - start < time;) {
    if(func() == 2){
      return;
    }
  }
}

/**
 * @brief Wrapper que ejecuta una funcion por un tiempo determinado, se usa para ejecutar la funcion de reposo, este se ejecuta hasta que pase el tiempo o hasta que se registre una aceleración anormal.
 * 
 * @param time 
 * @param min_acelerometro | minimo de aceleracion para que se ejecute la funcion
 * @param func 
 */
void timeWrapper(unsigned long time, int min_acelerometro, bool (*func)(int)) {
  for (unsigned long start = millis(); millis() - start < time;) {
    bool mybool = func(min_acelerometro);
    if (mybool) {
      return;
    } 
  }
}

/**
 * @brief Wrapper que sirve para envolver la funcion y que se encienda el pin 2 mientras se ejecuta la funcion.
 * 
 * @param func byte 
 */
byte pinWrapper(byte (*func)()) {
  digitalWrite(2, HIGH);
  byte status = func();
  digitalWrite(2, LOW);
  return status;
}

/**
 * @brief Wrapper que sirve para envolver la funcion y que se encienda el pin 2 mientras se ejecuta la funcion.
 * 
 * @param data String
 * @param func byte
 * @return byte  
 */
byte pinWrapper(String data, byte (*func)(String)) {
  digitalWrite(2, HIGH);
  byte status = func(data);
  digitalWrite(2, LOW);
  return status;
}

/**
 * @brief Wrapper que sirve para envolver la funcion y que se encienda el pin 2 mientras se ejecuta la funcion.
 * 
 * @param data const char *
 * @param data1 const char *
 * @param data2 const char *
 * @param func byte
 * @return byte  
 */
byte pinWrapper(const char *data, const char *data1, const char *data2, byte (*func)(const char *, const char *, const char *)) {
  digitalWrite(2, HIGH);
  byte status = func(data, data1, data2);
  digitalWrite(2, LOW);
  delay(200);
  return status;
}