#include "Arduino.h"

namespace mc {

class MotorController {
  public:
    MotorController() {};
    String getFWVersion();
    void reboot();
    void ping();
    float getTemperature();
};
}
