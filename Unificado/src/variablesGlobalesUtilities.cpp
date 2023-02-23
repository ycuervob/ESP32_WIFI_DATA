#include "variablesGlobalesUtilities.h"
#include "func/storeUtilities.h"
#include "dataTypes.h"


// Variables globales para el manejo de las variables globales.
globVars gVars;
// variable que sirve para saber si es la primera vez que se ejecuta el programa.
bool only_first_time = true;

globVars getGlobalVar()
{
    return gVars;
}

/**
 * @brief Inicializa las variables globales basado en la lectura de la micro sd de los archivos de configuración.
 */
void initGlobalVar()
{
    if (only_first_time)
    {
        String files[13] = {"/device.txt", "/ssid.txt", "/pass.txt", "/server.txt", "/maxT.txt", "/maxV.txt", "/minV.txt", "/Tlectura.txt", "/Tenviado.txt", "/porEnviado.txt", "/max_acel.txt", "/tiempo_espera_wifi.txt", "/tiempo_conexion_wifi.txt"};
        getVariables(gVars, files);
        only_first_time = false;
        
    }
}

/**
 * @brief Retorna el intervalo de tiempo de un ciclo del programa.
 * Este intervalo se dividirá en 3 partes: tiempo de lectura, tiempo de envio y tiempo de espera.
 *
 * @return int
 */
int tiempoEspera()
{
    if (gVars.velocidad <= gVars.vel_reposo_max)
    {
        return gVars.tiempo_max * 60000;
    }
    else if (gVars.velocidad > gVars.vel_reposo_max && gVars.velocidad <= gVars.vel_no_reposo)
    {
        return (gVars.tiempo_max - (gVars.velocidad / (gVars.vel_no_reposo / 10))) * 60000; // funcion de tiempo
    }
    else
    {
        return 0;
    }
}

/**
 * @brief Calcula el tiempo de envio en base al tiempo de espera y el porcentaje de envio.
 * Retorna 0 si el tiempo de envio es menor al min_tiempo_enviado almacenado en la variable global.
 * @return int
 */
int tiempoEnvio(int tiempo_esp)
{
    return (tiempo_esp / gVars.porcentaje_enviado) >= gVars.min_tiempo_enviado * 1000 ? (tiempo_esp / gVars.porcentaje_enviado) : 0;
}