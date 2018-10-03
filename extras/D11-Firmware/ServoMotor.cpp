#include "ServoMotor.h"

void ServoMotor::setDuty(int duty) {
  this->duty = duty;
  if (duty < 0) {
    pinMode(pin, INPUT);
  } else {
    analogWrite(pin, duty);
  }
}

void ServoMotor::setFrequency(int frequency) {
  // NB: not implemented at the moment!
  //this->frequency = frequency;
}
