#include "TurnSensor.h"


#define READ_DELAY  15
#define TIMEOUT     3000

TurnSensor* TurnSensor::instance = NULL;


TurnSensor* TurnSensor::getInstance() {
  if (instance == NULL) {
    instance = new TurnSensor();
  }
  return instance;
}

// This is only required for absolute angle based on a fixed starting point
//void TurnSensor::calibrateTurnSensor() {
//
//
//  // Calibrate the gyro->
//  float total = 0;
//  for (int i = 0; i < 1024; i++)
//  {
//    M5.MPU6886.getGyroData(&gyroX, &gyroY, &gyroZ);
//    // Add the Z axis reading to the total.
//    total += gyroZ;
//  }
//
//  gyroOffset = total / 1024.;
//
//}

// This start a relative angle measurement
// If you are using absolute angle ie, calibrateTurnSensor, you won't be using this method
void TurnSensor::resetTurnSensor() {
  gyroLastUpdate = micros();
  turnRate = turnAngle = 0.;

  // set offset base on current gyro reading
  M5.MPU6886.getGyroData(&gyroX, &gyroY, &gyroZ);
  gyroOffset = gyroZ;
//  delay(10);
//  updateTurnSensor();
}

// accumulate total angle turned via gyro reading
void TurnSensor::updateTurnSensor() {
  // Read the measurements from the gyro->
  M5.MPU6886.getGyroData(&gyroX, &gyroY, &gyroZ);
  turnRate = gyroZ - gyroOffset;

  // Figure out how much time has passed since the last update (dt)
  unsigned long m = micros();
  unsigned long dt = m - gyroLastUpdate;
  gyroLastUpdate = m;

  // Multiply dt by turnRate in order to get an estimation of how
  // much the robot has turned since the last update.
  // (angular change = angular velocity * time)

  turnAngle += turnRate * float(dt) / 1000000.;

//  gyroOffset = gyroZ;  

}
  
TurnSensor::TurnSensor() {

  gyroLastUpdate = 0;
  gyroOffset = turnAngle = turnRate = gyroX = gyroY = gyroZ = 0.;
  M5.MPU6886.Init();
  M5.MPU6886.SetGyroFsr(M5.MPU6886.GFS_500DPS);
}

int32_t TurnSensor::getTurnAngle() {
  return (int32_t) turnAngle;
}

float TurnSensor::getTurnRate() {
  return turnRate;
}

float TurnSensor::getGyroOffset() {
  return gyroOffset;
}

void TurnSensor::waitTillTurnedNumberOfDegreesRight(int32_t degrees) {

  resetTurnSensor();

  //updateTurnSensor();
  int32_t startAngle = getTurnAngle();
  int32_t target = degrees + startAngle;
  unsigned long startTime = millis();

   do {
    delay(READ_DELAY);
    updateTurnSensor();
    // terminate on timeout to avoid deadlock
  } while ((getTurnAngle() < target) and (millis() - startTime < TIMEOUT));

}

void TurnSensor::waitTillTurnedNumberOfDegreesLeft(int32_t degrees) {
  
  resetTurnSensor();

  //updateTurnSensor();
  int32_t startAngle = getTurnAngle();
  int32_t target = -degrees + startAngle;
  unsigned long startTime = millis();

   do {
    delay(READ_DELAY);
    updateTurnSensor();
    // terminate on timeout to avoid deadlock
  } while ((getTurnAngle() > target) and (millis() - startTime < TIMEOUT));

}
