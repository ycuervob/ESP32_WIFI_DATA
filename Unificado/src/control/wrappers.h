// Se incluye solo la biblioteca Arduino.h porque es la única utilizada en este archivo.
#ifndef WRAPPERS_H
#define WRAPPERS_H

void timeWrapper(unsigned long time, void (*func)());
void timeWrapper(unsigned long time, byte (*func)());
void timeWrapper(unsigned long time, int min_acelerometro, bool (*func)(int));
byte pinWrapper(byte (*func)());
byte pinWrapper(String data, byte (*func)(String));
byte pinWrapper(const char *data, const char *data1, const char *data2, byte (*func)(const char *, const char *, const char *));

#endif // MYFILE_H