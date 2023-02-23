#include <ArduinoJson.h>
#include "variablesGlobalesUtilities.h"
#include "func/storeUtilities.h"
#include "componentes/wifiUtilities.h"
#include "dataTypes.h"

// Variables globales para el manejo de las variables globales.
globVars gVars;

globVars getGlobalVar()
{
    return gVars;
}

void setVelocidad(int velocidad)
{
    gVars.velocidad = velocidad;
}

/**
 * @brief Inicializa las variables globales basado en la lectura de la micro sd de los archivos de configuración.
 */
void initGlobalVar()
{
    String vars = getVariables();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, vars.c_str());
    const char * device = doc["device"];
    const char * ssid = doc["ssid"];
    const char * pass = doc["pass"];
    const char * server = doc["server"];
    gVars.device = String(device);
    gVars.ssid = String(ssid);
    gVars.pass = String(pass);
    gVars.server = String(server);
    gVars.tiempo_max = (int)doc["tiempo_max"];
    gVars.vel_no_reposo = (int)doc["vel_no_reposo"];
    gVars.vel_reposo_max = (int)doc["vel_reposo_max"];
    gVars.tiempo_lectura_guardado = (int)doc["tiempo_lectura_guardado"];
    gVars.min_tiempo_enviado = (int)doc["min_tiempo_enviado"];
    gVars.porcentaje_enviado = (int)doc["porcentaje_enviado"];
    gVars.acelerometro_anormal = (int)doc["acelerometro_anormal"];
    gVars.tiempo_espera_modem = (int)doc["tiempo_espera_modem"];
    gVars.tiempo_epera_conexion = (int)doc["tiempo_epera_conexion"];
}

void initGrupoLectura()
{
    gVars.id_grupo_lectura = getGrupoLectura();
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