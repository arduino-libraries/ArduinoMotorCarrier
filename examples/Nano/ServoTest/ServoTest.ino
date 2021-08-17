
#include <ArduinoMotorCarrier.h>
#define INTERRUPT_PIN 6


void setup()
{
  //Serial port initialization
  Serial.begin(115200);
  //while (!Serial);

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

  M1.setDuty(0);
  M2.setDuty(0);
  M3.setDuty(0);
  M4.setDuty(0);
}

void loop() {

  //Servo sweep from 0 position to 180
  for (int i = 0; i < 180; i += 1)
  {
    //Choose what of all the servo connectors do you want to use: servo1(default), servo2, servo3 or servo4
    servo1.setAngle(i);
    servo2.setAngle(i);
    servo3.setAngle(i);
    servo4.setAngle(i);
    Serial.print("Servos position");
    Serial.println(i);
    delay(100);
  }

  delay(200);

  //Servo sweep from 180 position to 0
  for (int i = 180; i > 0; i -= 1)
  {
    //Choose what of all the servo connectors do you want to use: servo1(default), servo2, servo3 or servo4
    servo1.setAngle(i);
    servo2.setAngle(i);
    servo3.setAngle(i);
    servo4.setAngle(i);
    Serial.print("Servos position: ");
    Serial.println(i);
    delay(100);
  }

  delay(200);
}
