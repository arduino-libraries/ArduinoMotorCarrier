#include "Arduino.h"

namespace mc {

class ServoMotor {
  public:
    ServoMotor();
    void setAngle(int angle);
    void setFrequency(int frequency);
  private:
    int instance;
};
}
