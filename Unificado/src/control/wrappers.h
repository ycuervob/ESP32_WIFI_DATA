// Se incluye solo la biblioteca Arduino.h porque es la única utilizada en este archivo.
#ifndef WRAPPERS_H
#define WRAPPERS_H

void timeWrapper(unsigned long time, void (*func)());
void timeWrapper(unsigned long time, byte (*func)());
void timeWrapper(unsigned long time, int min_acelerometro, bool (*func)(int));

#endif // MYFILE_H