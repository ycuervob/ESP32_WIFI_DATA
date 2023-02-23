#include <Arduino.h>
#include "../componentes/pinnesUtilities.h"

/**
 * @brief Wrapper que ejecuta una funcion por un tiempo determinado.
 *
 * @param time
 * @param func
 */
void timeWrapper(unsigned long time, void (*func)())
{
  for (unsigned long start = millis(); millis() - start < time;)
  {
    func();
  }
}

/**
 * @brief Wrapper que ejecuta una funcion por un tiempo determinado.
 *
 * @param time
 * @param func byte 2: NO MAS DATOS
 */
void timeWrapper(unsigned long time, byte (*func)())
{
  for (unsigned long start = millis(); millis() - start < time;)
  {
    if (func() == 2)
    {
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
void timeWrapper(unsigned long time, int min_acelerometro, bool (*func)(int))
{
  encenderLed('c', true);
  encenderLed('e', true);
  encenderLed('w', true);
  encenderLed('s', true);
  for (unsigned long start = millis(); millis() - start < time;)
  {
    bool mybool = func(min_acelerometro);
    if (mybool)
    {
      encenderLed('c', false);
      encenderLed('e', false);
      encenderLed('w', false);
      encenderLed('s', false);
      return;
    }
  }
}