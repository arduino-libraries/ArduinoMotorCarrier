#include "Encoder.h"
#include "Wire.h"
#include "Common.h"

static int next_instance = 0;

mc::Encoder::Encoder() {
  instance = next_instance;
  next_instance++;
};

void mc::Encoder::resetCounter(long value) {
  setData(RESET_COUNT_ENCODER, instance, value);
}

int mc::Encoder::getRawCount() {
  int ret;
  getData(GET_RAW_COUNT_ENCODER, instance, (uint8_t*)&ret);
  return ret;
}

int mc::Encoder::getOverflowUnderflow() {
  uint8_t ret[2];
  getData(GET_OVERFLOW_UNDERFLOW_STATUS_ENCODER, instance, (uint8_t*)ret);
  return ret[0] << 8 | ret[1];
}

int mc::Encoder::getCountPerSecond() {
  int ret;
  getData(GET_COUNT_PER_SECOND_ENCODER, instance, (uint8_t*)&ret);
  return ret;
}

void mc::Encoder::setIrqOnCount(long value) {
  setData(SET_INTERRUPT_ON_COUNT_ENCODER, instance, value);
}

void mc::Encoder::setIrqOnVelocity(long value, uint8_t margin) {
  setData(SET_INTERRUPT_ON_VELOCITY_ENCODER, instance, (margin << 24 | value));
}
