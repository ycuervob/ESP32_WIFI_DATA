#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include <cstdlib>
#include "sdUtilities.h"
#include "pinnesUtilities.h"

// Variables globales para el manejo de la micro SD
File myFile, fileLine;

/**
 * @brief Inicializa la micro SD y retorna true si se pudo conectar, false si no se pudo conectar en 10 segundos.
 *
 * @return true
 * @return false
 */
bool sdInicializacion()
{
  unsigned long start = millis();
  encenderLed('s', false);
  while (!SD.begin(SS))
  {
    if (millis() - start > 5000)
    { // Se intenta conectar por 10 segundos
      return false;
    }
  }
  encenderLed('s', true);
  return true;
}

/**
 * @brief Termina la conexión con la micro SD y luego espera 200 milisegundos.
 */
void endSD()
{
  SD.end();
  delay(200);
}

/**
 * @brief Guarda los datos en el archivo data.json de la micro SD si el archivo ya tiene datos, los agrega al final del archivo.
 *
 * @param postData : String
 * @return true si se guardaron los datos
 * @return false si no se guardaron los datos
 */
bool saveDataSD(String postData)
{
  myFile = SD.open("/data.json", FILE_APPEND);
  bool datosGuardados = false;
  int string_len = postData.length() + 1;
  char Buf[string_len];
  postData.toCharArray(Buf, string_len);

  if (myFile)
  {
    myFile.println(Buf);
    datosGuardados = true;
  }
  else
  {
    datosGuardados = false;
  }

  myFile.close();
  return datosGuardados;
}

/**
 * @brief Lee un entero de la micro SD y lo guarda en el puntero *position_var
 *
 * @param filename
 * @param position_var
 */
void getLine(String &filename, int *position_var)
{
  fileLine = SD.open(filename.c_str());
  if (fileLine)
  {
    char value[fileLine.size()];
    fileLine.readBytes(value, fileLine.size());
    *position_var = atoi(value);
  }
  fileLine.close();
}

/**
 * @brief Lee una linea del archivo de la micro SD y lo guarda en el puntero *value
 *
 * @param filename Nombre del archivo a leer
 * @param value Puntero donde se retoranará la linea leida de la micro SD
 */
void getLine(const char *filename, String *value)
{
  fileLine = SD.open(filename);
  if (fileLine)
  {
    while (fileLine.available())
    {
      String c = String((char)fileLine.read());

      if (c != "\n" && c != "\r" && c != " ")
        *value += c;
    }
  }
  else
  {
    *value = String("NO_DATO_DISPONIBLE_SD");
  }
  fileLine.close();
}

/**
 * @brief Guarda en el archivo currentLine.txt de la micro SD el valor de la posición en la que se quedó al guardar los datos.
 *
 * @param position_var int *
 */
void setLine(int *position_var)
{
  fileLine = SD.open("/currentLine.txt", FILE_WRITE);
  if (fileLine)
  {
    fileLine.println(*position_var);
  }
  fileLine.close();
}

/**
 * @brief   Lee una linea y retorna la posición en la que quedó (byte) al dejar de leer la linea.
  Estados:

 *
 * @param linea String *
 * @param posicion_var  int *
 * @return byte ARCHIVO_NO_ABIERTO 0 | LEIDO 1 | NO_MAS_DATOS 2
 */
byte readLine(String *linea, int *posicion_var)
{
  myFile = SD.open("/data.json");
  byte linea_leida = 0;
  int fileSize = myFile.size();

  if (myFile)
  {
    if (*posicion_var < fileSize)
    {
      myFile.seek(*posicion_var);
      *linea = myFile.readStringUntil('\n');
      *posicion_var = myFile.position();
      linea_leida = 1;
      myFile.close();
      return linea_leida;
    }
    else if (*posicion_var >= fileSize)
    {
      linea_leida = 2;
      *posicion_var = 0;
      myFile.close();
      SD.remove("/currentLine.txt");
      SD.remove("/data.json");
      return linea_leida;
    }
  }

  myFile.close();
  delay(2000);
  return linea_leida;
}