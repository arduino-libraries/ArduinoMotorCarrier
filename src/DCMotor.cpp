#include "DCMotor.h"
#include "Common.h"

namespace mc {
static int next_instance = 0;

DCMotor::DCMotor() {
  instance = next_instance;
  next_instance++;
};

void DCMotor::setDuty(int duty) {
  setData(SET_PWM_DUTY_CYCLE_DC_MOTOR, instance, duty);
}

void DCMotor::setFrequency(int frequency) {
  setData(SET_PWM_FREQUENCY_DC_MOTOR, instance, frequency);
}

}
// D21 implementations

namespace d21 {
static int next_instance = 0;

DCMotor::DCMotor() {
  instance = next_instance;
  next_instance++;
  if (instance == 0) {
    in1 = MOTOR_3_PIN_A; //2;
    in2 = MOTOR_3_PIN_B; //3;
  } else {
    in1 = MOTOR_4_PIN_A; //5;
    in2 = MOTOR_4_PIN_B; //4;
  }
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
};

void DCMotor::setDuty(int duty) {
  //setData(SET_PWM_DUTY_CYCLE_DC_MOTOR, instance, duty);
  this->duty = duty;
  if (duty == 0) {
    analogWrite(in1, 0);
    analogWrite(in2, 0);
    return;
  }
  if (duty > 0) {
    analogWrite(in1, 0);
    analogWrite(in2, map(duty, 0, 100, 0, 255));
  } else {
    analogWrite(in2, 0);
    analogWrite(in1, map(-duty, 0, 100, 0, 255));
  }

}

void DCMotor::setFrequency(int frequency) {
  //setData(SET_PWM_FREQUENCY_DC_MOTOR, instance, frequency);
}
}
