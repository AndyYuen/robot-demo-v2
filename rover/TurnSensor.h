#ifndef TurnSensor_h
#define TurnSensor_h

#include <M5StickC.h>

// This module uses the MPU6886 library
class TurnSensor
{
public:
  
  static TurnSensor *getInstance();

//  void calibrateTurnSensor();
  void resetTurnSensor();
  void updateTurnSensor();
  int32_t getTurnAngle();
  float getTurnRate();
  float getGyroOffset();

  void waitTillTurnedNumberOfDegreesLeft(int32_t degrees);
  void waitTillTurnedNumberOfDegreesRight(int32_t degrees);

private:
  TurnSensor();
  
  float gyroX;
  float gyroY;
  float gyroZ;
  static TurnSensor *instance;
  float turnAngle;
  float turnRate;
  float gyroOffset;
  unsigned long gyroLastUpdate;

};
#endif
