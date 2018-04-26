#include <Wire.h>
#include "Encoder.h"
#include "Battery.h"
#include "DCMotor.h"
#include "ServoMotor.h"
#include "MotorController.h"
#include "Common.h"
#include "PID.h"

void setDataPIDGains(Commands cmd, uint8_t target, int16_t P, int16_t I, int16_t D);
void setData(Commands cmd, uint8_t target, int data);
int getData(Commands cmd, uint8_t target, uint8_t* buf);
int getData(Commands cmd, uint8_t* buf);

