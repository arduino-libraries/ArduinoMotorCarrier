# ArduinoMotorCarrier library

## Methods

### `BATTERY`

Returns information about the battery connected to the carrier.

#### Syntax

```
battery.getRaw()
battery.getConverted()
battery.getFiltered()
```

#### Returns

* _getRaw()_: returns the raw ADC read from the battery as an integer.
* _getConverted()_: returns the battery voltage converted to volts as a floating point.
* _getFiltered()_: returns the battery voltage converted to volts and filtered in the last 10 seconds.


#### Example

```

#include <ArduinoMotorCarrier.h>

//Variable to store the battery voltage
float batteryVoltage;
...
void loop() {
  batteryVoltage = battery.getRaw()/236.0; //236 for Nano, 77 for MKR.
  Serial.print("Battery voltage: ");
  Serial.print(batteryVoltage,3);  
  Serial.print("V, Raw ");
  Serial.println(battery.getRaw());
  delay(5000); //wait for a few seconds  
}
```

### `SERVO`

Represent the servomotors available on the MotorCarrier. There are 4 headers for servomotors.

#### Syntax

```
servo1.setAngle(int)
servo2.setAngle(int)
servo3.setAngle(int)
servo4.setAngle(int)
```

#### Function

* _setAngle(int)_: Set the rotation angle (from 0 to 180)


### `MOTOR`

There is 4 objects pointing to each possible motor: M1, M2, M3 and M4.

#### Syntax

````
M1.setDuty(int)
M2.setDuty(int)
M3.setDuty(int)
M4.setDuty(int)
````

#### Functions

* _setDuty(int)_: Set the duty cycle of the dc motor (from -100 to +100) , 0 means stop.


### `ENCODER`

Represents the 2 quadrature encoders embedded in the carrier board. The two objects are encoder1 and encoder2.

#### Syntax

````
encoder1.getRawCount()
encoder2.resetCounter();
````

#### Functions

* _getRawCount()_: Returns the number of counts from start as an integer.
* _resetCounter(int)_: Resets counter to a certain value.


### `CONTROLLER`

Represents the motor shield controller and exposes some high level functions. It also configures the battery charger (only on the NanoMotorCarrier) to start charging the battery.

#### Syntax

```
controller.getFWVersion()
controller.reboot()
```
### `PID`

Allow setting Motor1 or Motor2 to a specific speed or position. There are two PID virtual objects in the controller: pid1 and pid2. pid1 acts on M1 and encoder1. pid2 acts on M2 and encoder2. It is advisable to control the motors using these functions.

#### Syntax

```
pid1.setGains(float P, float I, float D)
```

#### Functions

* _setGains(float P, float I, float D)_: Set PID gains.
* _resetGains()_: Reset PID gains to factory default settings.
* _setControlMode(cl_control)_: Set control mode to either `CL_VELOCITY` or `CL_POSITION`.
* _setSetpoint(cl_mode, int target)_: Set a specific velocity or position in one of the motors. Define cl_mode as `TARGET_POSITION` or `TARGET_VELOCITY` and the desired value in target.

#### Example

Example for PID position control. 

```
#include <ArduinoMotorCarrier.h>
#define INTERRUPT_PIN 6

//Variable to change the motor speed and direction
static int duty = 0;

int target;
float P;
float I;
float D;

void setup()
{
  //Serial port initialization
  Serial.begin(115200);
  while (!Serial);

  //Establishing the communication with the motor shield
  if (controller.begin())
  {
    Serial.print("MKR Motor Shield connected, firmware version ");
    Serial.println(controller.getFWVersion());
  }
  else
  {
    Serial.println("Couldn't connect! Is the red led blinking? You may need to update the firmware with FWUpdater sketch");
    while (1);
  }

  // Reboot the motor controller; brings every value back to default
  Serial.println("reboot");
  controller.reboot();
  delay(500); 

  int dutyInit = 0; 
  M1.setDuty(dutyInit);
  M2.setDuty(dutyInit);
  M3.setDuty(dutyInit);
  M4.setDuty(dutyInit);
  Serial.print("Duty: ");
  Serial.println(dutyInit);

  P = 0.07f;//0.07 //0.2
  I = 0.0f;
  D = 0.007f;

  /************* PID 1 ***********************/

  pid1.setControlMode(CL_POSITION);

  //pid1.resetGains();  
  pid1.setGains(P, I, D); //Proportional(change) Integral(change) Derivative
  Serial.print("P Gain: ");
  Serial.println((float)pid1.getPgain());
  Serial.print("I Gain: ");
  Serial.println((float)pid1.getIgain());
  Serial.print("D Gain: ");
  Serial.println((float)pid1.getDgain(), 7);
  Serial.println("");

  encoder1.resetCounter(0);
  Serial.print("encoder1: ");
  Serial.println(encoder1.getRawCount());
  target = 5000;
  pid1.setSetpoint(TARGET_POSITION, target);
}

void loop() {

  Serial.print("encoder1: ");
  Serial.print(encoder1.getRawCount());
  Serial.print(" target: ");
  Serial.println(target);
  if (encoder1.getRawCount() == target) {
    target += 1000;
    Serial.print("Target reached: Setting new target..");
    pid1.setSetpoint(TARGET_POSITION, target);
    //delay(5000);
  }

  delay(50);
}
```
