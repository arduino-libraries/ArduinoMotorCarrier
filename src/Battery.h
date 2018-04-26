#include "Arduino.h"

namespace mc {

class Battery {
  public:
    Battery();
    int getRaw();
    int getConverted();
    int getFiltered();
};
}
