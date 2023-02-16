#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>
#include "acelerometroUtilities.h"
#include "../global/dataTypes.h"

//Variable globar para el manejo del acelerometro.
Adafruit_MPU6050 mpu;

/**
 * @brief Inicializa el acelerometro y retorna true si se pudo inicializar, false si no se pudo inicializar.
 * 
 * @return true 
 * @return false 
 */
bool acelerometroInicializacion() {
  // Try to initialize!
  if (!mpu.begin()) {
    return false;
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  return true;
}

/**
 * @brief Lee los datos del acelerometro y los guarda en la estructura dataAcelerometro.
 * 
 * @param dataAcelerometro aceleraometroDataType ver el archivo `dataTypes.h`
 */
void acelerometro(acelerometroDataType & dataAcelerometro) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  dataAcelerometro.x = String(a.acceleration.x, 6);
  dataAcelerometro.y = String(a.acceleration.y, 6);
  dataAcelerometro.z = String(a.acceleration.z, 6);
  dataAcelerometro.total = String(sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)), 6);
}

/**
 * @brief Retorna true si el valor del acelerometro es mayor a alt_val, false si no lo es.
 * 
 * @param alt_val int
 * @return true 
 * @return false 
 */
bool acelerometroAlto(int alt_val) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float value = sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2));   
  if (value > alt_val) {
    return true;
  } else {
    return false;
  }
}