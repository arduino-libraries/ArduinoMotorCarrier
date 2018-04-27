#include <Wire.h>
#include "Encoder.h"
#include "Battery.h"
#include "DCMotor.h"
#include "ServoMotor.h"
#include "MotorController.h"
#include "Common.h"
#include "PID.h"

extern mc::MotorController controller;

extern mc::ServoMotor servo1;
extern mc::ServoMotor servo2;
extern mc::ServoMotor servo3;
extern mc::ServoMotor servo4;

extern mc::DCMotor M1;
extern mc::DCMotor M2;
extern d21::DCMotor M3;
extern d21::DCMotor M4;

extern mc::Encoder encoder1;
extern mc::Encoder encoder2;

extern mc::PID pid1;
extern mc::PID pid2;

extern mc::Battery battery;
