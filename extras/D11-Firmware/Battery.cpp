#include "Battery.h"
#include "Events.h"
#include "Wire.h"

#define SCALE_FACTOR  (77)

void Battery::readBattery() {
  index++;
  index = index%10;
  readBuf[index] = (int)analogRead(pin);
}

void readBattery_wrapper(void* arg)
{
  Battery* obj = (Battery*)arg;
  obj->readBattery();
}

Battery::Battery(int pinA) {
  pin = pinA;
  registerTimedEvent(readBattery_wrapper, this, 1000);
  readBuf[0] = (int)analogRead(pin);
}

void Battery::getRaw() {
  Wire.write(readBuf[index]);
}

void Battery::getConverted() {
  Wire.write(readBuf[index] / SCALE_FACTOR);
}

void Battery::getFiltered() {
  long total = 0;
  for (int i = 0; i < 10; i++) {
    total += readBuf[i];
  }
  Wire.write((int)(total/(10*SCALE_FACTOR)));
}
