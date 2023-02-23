#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "dataTypes.h"

globVars getGlobalVar();
void initGlobalVar();
int tiempoEspera();
int tiempoEnvio(int tiempo_esp);
void setVelocidad(int velocidad);
void initGrupoLectura();

#endif // UTILITIES_H