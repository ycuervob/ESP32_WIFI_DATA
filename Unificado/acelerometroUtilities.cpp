#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "utilities.h"

// Accelerometer
Adafruit_MPU6050 mpu;


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

acelerometroDataType acelerometro() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  acelerometroDataType dataAcelerometro;
  dataAcelerometro.x = String(a.acceleration.x, 6);
  dataAcelerometro.y = String(a.acceleration.y, 6);
  dataAcelerometro.z = String(a.acceleration.z, 6);
  dataAcelerometro.total = String(sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)), 6);
  return dataAcelerometro;
}

bool acelerometroAlto() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if (sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)) > 20) {
    return true;
  } else {
    return false;
  }
}