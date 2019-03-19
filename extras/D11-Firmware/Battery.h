#include "Arduino.h"

class Battery {
  public:
    Battery(int pinA);
    void getRaw();
    void getConverted();
    void getFiltered();
    void readBattery();
  private:
    int pin = -1;
    int readBuf[10];
    uint8_t index = 0;
};
