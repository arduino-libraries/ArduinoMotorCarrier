#include "DCMotor.h"

void DCMotor::setDuty(int duty) {
  this->duty = duty;
  if (duty == 0) {
    analogWrite(in1, 0);
    analogWrite(in2, 0);
    return;
  }

  // scale duty to period
  //duty = duty * 255 / 100;
  duty = duty * 16777215/ 100; //due to new servo resolution

  if (duty > 0) {
    analogWrite(in1, 0);
    analogWrite(in2, duty);
  } else {
    analogWrite(in2, 0);
    analogWrite(in1, -duty);
  }
}

void DCMotor::setFrequency(int frequency) {
  // NB: not implemented at the moment!
  //this->frequency = frequency;
}
