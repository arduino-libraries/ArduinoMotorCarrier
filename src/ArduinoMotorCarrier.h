/*
  ArduinoMotorCarrier.h - Library for Arduino Motor Shields
  Copyright (c) 2018-2019 Arduino AG.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __ARDUINOMOTORSHIELD__
#define __ARDUINOMOTORSHIELD__

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

#endif
