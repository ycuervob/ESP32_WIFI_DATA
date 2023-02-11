#include <Arduino.h>
#include "utilities.h"

//Variables globales para el manejo de la bateria.
const int pinBateria = 35;
byte x = 1;
byte y = 1;
int bateria = 0;

//Variables globales para el manejo de las variables globales. 
globVars gVars;
globVars nFiles;

//variable que sirve para saber si es la primera vez que se ejecuta el programa.
bool only_first_time = true;

/**
 * @brief Retorna el intervalo de tiempo de un ciclo del programa.
 * Este intervalo se dividirá en 3 partes: tiempo de lectura, tiempo de envio y tiempo de espera.
 * 
 * @return int 
 */
int tiempoEspera() {
  if (gVars.velocidad <= gVars.vel_reposo_max) {
    return gVars.tiempo_max * 60000;
  } else if (gVars.velocidad > gVars.vel_reposo_max && gVars.velocidad <= gVars.vel_no_reposo) {
    return (gVars.tiempo_max - (gVars.velocidad / (gVars.vel_no_reposo / 10))) * 60000;  //funcion de tiempo
  } else {
    return 0;
  }
}

/**
 * @brief Retorna el valor del tiempo de lectura almacenado en la variable global.
 * 
 * @return int 
 */
int tiempoLectura() {
  return gVars.tiempo_lectura_guardado;
}

/**
 * @brief Retorna el valor del tiempo de envio almacenado en la variable global.
 * 
 * @return int 
 */
int minAcelerometro() {
  return gVars.acelerometro_anormal;
}

/**
 * @brief Retorna el valor del tiempo que el dispositivo duerme mientras espera a que el wifi esté listo para conexión.
 * 
 * @return int 
 */
int tiempoEsperaWifi(){
  return gVars.tiempo_epera_conexion;
}

/**
 * @brief Retorna el valor del tiempo que el dispositivo intenta conectarse al wifi una vez el wifi está listo para conexión.
 * 
 * @return int 
 */
int tiempoConexionWifi(){
  return gVars.tiempo_conexion_wifi;
}

/**
 * @brief Calcula el tiempo de envio en base al tiempo de espera y el porcentaje de envio.
 * Retorna 0 si el tiempo de envio es menor al min_tiempo_enviado almacenado en la variable global.
 * @return int 
 */
int tiempoEnvio(int tiempo_esp) {
  return (tiempo_esp / gVars.porcentaje_enviado) >= gVars.min_tiempo_enviado * 1000 ? (tiempo_esp / gVars.porcentaje_enviado) : 0;
}

/**
 * @brief Inicializa las variables globales basado en la lectura de la micro sd de los archivos de configuración.
 */
void initGlobalVar() {
  if (only_first_time) {
    String files[13] = { "/device.txt", "/ssid.txt", "/pass.txt", "/server.txt", "/maxT.txt", "/maxV.txt", "/minV.txt", "/Tlectura.txt", "/Tenviado.txt", "/porEnviado.txt", "/max_acel.txt", "/tiempo_espera_wifi.txt", "/tiempo_conexion_wifi.txt" };
    getVariables(gVars, files);
    only_first_time = false;
  }
}

/**
 * @brief Crea un dato sipo paqueteDataType con los datos de los sensores y lo almacena en la micro sd.
 * Si no hay micro sd, se reintenta conectar a la micro sd hasta que se conecte o se pase el tiempo de 5 segundos.
 * Si no se puede conectar a la micro sd, se descartan los datos.
 */
void almacenamientoDatos() {
  paqueteDataType dataToPost;
  tempyhumedad(dataToPost.temyhDatos);
  gpsDatos(dataToPost.gpsDatos);
  acelerometro(dataToPost.acelerometroDatos);
  termocupla(dataToPost.termocuplaDatos);
  gVars.velocidad = dataToPost.gpsDatos.velocidad;
  dataToPost.bateria = analogRead(pinBateria);
  dataToPost.id_device = gVars.device;
  String postData = createPostData(dataToPost);
  byte status = pinWrapper(postData, &guardaDatosSD);

  unsigned long start = millis();
  while (status == NOT_SD) {
    endSD();
    sdInicializacion();
    status = pinWrapper(postData, &guardaDatosSD);
    if (millis() - start > 5000) {
      break;
    }
  }


  char *estados_general[4] = { "Datos erroneos, descartados", "No hay SD datos descartados", "Almacenado" };
  Serial.println(estados_general[status]);
  char Buf[postData.length() + 1];
  postData.toCharArray(Buf, postData.length() + 1);
  Serial.println(Buf);
}

/*

*/

/**
 * @brief Función que envia los datos de la micro sd al servidor retorna el estado del envio.
 * 
 * @return byte | ARCHIVO_NO_ABIERTO 0 1 | LEIDO 1 | NO_MAS_DATOS 2 | LEIDO_PERO_NO_ENVIADO 3
 */
byte envioInformacion() {
  byte status = pinWrapper(gVars.server.c_str(), gVars.ssid.c_str(), gVars.pass.c_str(), &sendSDtoServer);
  char *estados_general[7] = { "ARCHIVO_NO_ABIERTO", "LEIDO", "NO_MAS_DATOS", "LEIDO_PERO_NO_ENVIADO", "FALLO_AL_ENVIAR", "ENVIADO", "NO_WIFI" };
  Serial.println(estados_general[status]);
  return status;
}

/**
 * @brief Funcion que sirve para inicializar la micro sd e imprimir por serial si se inicializo o no.
 * 
 */
void initSD() {
  bool init_sd = sdInicializacion();
  Serial.println(init_sd ? "si sd" : "no sd");
}

/**
 * @brief Funcion que sirve para inicializar el wifi e imprimir por serial si se inicializo o no.
 * 
 */
void initWIFI() {
  bool init_wifi = wifiInicializacion(gVars.ssid.c_str(), gVars.pass.c_str());
  Serial.println(init_wifi ? "si wifi" : "no wifi");
}