#include "src/Encoder/Encoder.h"
#include "src/FpF.hpp"

#define Fix16 mn::MFixedPoint::FpF32<8>

class EncoderWrapper {
  public:
    EncoderWrapper(int pinA, int pinB, int index);
    void getRawCount();
    void getOverflowUnderflow();
    void getCountPerSecond();
    void resetCounter(long value);
    int read();
    void setIrqOnCount(long value) {
      targetCount = value;
      irqCountEnabled = true;
    }
    void setIrqOnVelocity(long value) {
      if (value != 0) {
        targetVelocity = Fix16(value & 0xFFFFFF);
        //irqRatio = Fix16(value >> 24) / 100.0f;
        irqVelocityEnabled = true;
      } else {
        irqVelocityEnabled = false;
      }
    }
    bool underflow;
    bool overflow;
    Fix16 velocity;
    Fix16 position;
    Fix16 irqRatio = 2.0f;
    bool irqCountEnabled = false;
    bool irqVelocityEnabled = false;
    int targetCount = -1;
    Fix16 targetVelocity = -1.0;
  private:
    Encoder* enc;
};
