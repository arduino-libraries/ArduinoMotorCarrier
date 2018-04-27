#include "Battery.h"
#include "Events.h"
#include "Wire.h"

#define SCALE_FACTOR  (77)

void Battery::readBattery() {
  readBuf[index % 10] = (((int)analogRead(pin)) / SCALE_FACTOR);
  index ++;
}

void readBattery_wrapper(void* arg)
{
  Battery* obj = (Battery*)arg;
  obj->readBattery();
}

Battery::Battery(int pinA) {
  pin = pinA;
  registerTimedEvent(readBattery_wrapper, this, 1000);
}

void Battery::getRaw() {
  Wire.write((int)analogRead(pin));
}

void Battery::getConverted() {
  Wire.write((int)(analogRead(pin) / SCALE_FACTOR));
}

void Battery::getFiltered() {
  long total = 0;
  for (int i = 0; i < 10; i++) {
    total += readBuf[i];
  }
  Wire.write((int)(total/10));
}
