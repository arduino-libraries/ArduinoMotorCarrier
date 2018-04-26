#include "ServoMotor.h"
#include "Common.h"

static int next_instance = 0;

mc::ServoMotor::ServoMotor() {
  instance = next_instance;
  next_instance++;
};

void mc::ServoMotor::setAngle(int angle) {
  setData(SET_PWM_DUTY_CYCLE_SERVO, instance, map(angle,0,180,7,28));
}

void mc::ServoMotor::setFrequency(int frequency) {
  setData(SET_PWM_FREQUENCY_SERVO, instance, frequency);
}
