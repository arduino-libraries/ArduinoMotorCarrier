#include "Arduino.h"

namespace mc {

static volatile uint8_t irq_status;

class MotorController {
  public:
    MotorController() {};
    String getFWVersion();
    void reboot();
    void ping();
    float getTemperature();
};
}
