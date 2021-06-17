# ArduinoMotorCarrier library


This library allows you to use both the Arduino Nano Motor Carrier and the MKR Motor Carrier. The carrier supports inputs for servo motors, dc motors, and encoders, and can read the battery voltage level. This library, therefore, has functions and creates objects to support such hardware. In addition, the library supports PID control for position and velocity. Note that not all hardware features are supported in both carriers so take a look at the specifications for each board. You don't need to initiate any objects manually, they are automatically created when you include "ArduinoMotorCarrier.h"

To use this library:

```
#include <ArduinoMotorCarrier.h>
```

## Circuit

Connect the carrier to the main compatible board (MKR1010 or Nano 33 IoT), connect the LiPo battery, turn the switch on and connect the board to the computer using a micro USB cable. You can also connect the motors that you need for your project (servo or DC w/ or w/o encoders).

## Examples

* [Battery Read](https://docs.arduino.cc/tutorials/mkr-motor-carrier/mkr-motor-carrier-battery): Reading the battery level with the MKR Motor Carrier.
