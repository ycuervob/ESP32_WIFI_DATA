#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Accelerometer
Adafruit_MPU6050 mpu;

void acelerometroInicializacion() {
  if (!mpu.begin()) {
    ESP.restart();
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  //Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      //Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      //Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      //Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      //Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  //Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      //Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      //Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      //Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      //Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  //Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      //Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      //Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      //Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
     // Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      //Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      //Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      //Serial.println("5 Hz");
      break;
  }



}

double* acelerometro() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  double * acceArray = new double[4];
  acceArray[0] = a.acceleration.x;
  acceArray[1] = a.acceleration.y;
  acceArray[2] = a.acceleration.z;
  acceArray[2] = sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2));
  return acceArray;
}

bool acelerometroAlto (){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if(sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)) > 20){
    return true;
  }
  else {
    return false;
  }
    
  
}
