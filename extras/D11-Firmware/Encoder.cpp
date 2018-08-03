#include "EncoderWrapper.h"
#include "Wire.h"
#include "Events.h"
#include "Common.h"

static EncoderWrapper* obj[2] = {NULL, NULL};

#define VELOCITY_INTEGRATION_TIME   (1000)

void populateRegisters_wrapper(void* arg) {
  static long val[2];
  static long lastTimestampedVal[2];
  static long lastTimestamp;
  for (int i = 0; i < 2; i++) {
    int value = obj[i]->read();

    if (obj[i]->irqCountEnabled && (abs(value - obj[i]->targetCount) < 10 )) {
      requestAttention(ENCODER_COUNTER_REACHED);
    }
    if (value - val[i] < -30000) {
      obj[i]->underflow = true;
    }
    if (value - val[i] > 30000) {
      obj[i]->overflow = true;
    }

    //for now just use the difference in count since the last period as this is more than sufficient for now for use as angular velocity
    int16_t diff = value - lastTimestampedVal[i];
    obj[i]->velocity = Fix16(diff);
    lastTimestampedVal[i] = value;
    obj[i]->position = Fix16(value * 1.0f);

    // abs doesn't play well with Fix16 (missing an overload for minus)
    Fix16 ratioToTargetVelocityPercent = ((Fix16(obj[i]->velocity) - obj[i]->targetVelocity) * Fix16(100.0f)) / obj[i]->targetVelocity;

    if (obj[i]->irqVelocityEnabled && (ratioToTargetVelocityPercent < obj[i]->irqRatio) && (ratioToTargetVelocityPercent > (obj[i]->irqRatio * -1.0f) )) {
      requestAttention(ENCODER_VELOCITY_REACHED);
    }

    val[i] = value;
    lastTimestamp = millis();
  }
}

EncoderWrapper::EncoderWrapper(int pinA, int pinB, int index) {
  enc = new Encoder(pinA, pinB);
  obj[index] = this;
  if (index == 0) {
    registerTimedEvent(populateRegisters_wrapper, this, 10);
  }
}

int EncoderWrapper::read() {
  return enc->read();
}

void EncoderWrapper::resetCounter(long value) {
  enc->write(value);
}

void EncoderWrapper::getRawCount() {
  Wire.write(enc->read());
}

void EncoderWrapper::getOverflowUnderflow() {
  Wire.write(overflow);
  Wire.write(underflow);
}

void EncoderWrapper::getCountPerSecond() {
  Wire.write(int32_t(velocity));
  //  Wire.write(velocity);
}
