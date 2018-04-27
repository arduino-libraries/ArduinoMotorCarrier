#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__

#include "Arduino.h"

class DCMotor {
  public:
    DCMotor(Tc* tcc, int pinA, int pinB) : in1(pinA), in2(pinB) {
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
    };
    void setDuty(int duty);
    void setFrequency(int frequency);
    int duty = 0;
    void* pid;
  private:
    int in1;
    int in2;
    int frequency = 100;
};

#endif
