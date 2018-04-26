#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "Arduino.h"

namespace mc {

class Encoder {
  public:
    Encoder();
    int getRawCount();
    int getOverflowUnderflow();
    int getCountPerSecond();
    void resetCounter(long value);
    void setIrqOnCount(long value);
    void setIrqOnVelocity(long value, uint8_t margin = 2);
  private:
    int instance;
};
}

#endif
