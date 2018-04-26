#ifndef __DCMOTOR_H__
#define __DCMOTOR_H__

#include "Arduino.h"

namespace mc {

class DCMotor {
  public:
    DCMotor();
    void setDuty(int duty);
    void setFrequency(int frequency);
  private:
    int instance;
};
}

namespace d21 {

class DCMotor {
  public:
    DCMotor();
    void setDuty(int duty);
    void setFrequency(int frequency);
  private:
    int instance;
    int duty = 0;
    int in1;
    int in2;
};
}

#endif
