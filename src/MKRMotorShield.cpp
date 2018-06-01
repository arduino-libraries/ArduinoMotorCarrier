/*
  MKRMotorShield.cpp - Library for Arduino MKR Motor Shield
  Copyright (c) 2018 Arduino AG.  All right reserved.
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

#include "MKRMotorShield.h"

namespace mc {
void setDataPIDGains(Commands cmd, uint8_t target, int16_t P, int16_t I, int16_t D) {
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write((uint8_t)cmd);
  Wire.write((uint8_t)target);
  Wire.write((uint8_t*)&P, 2);
  Wire.write((uint8_t*)&I, 2);
  Wire.write((uint8_t*)&D, 2); 
  Wire.endTransmission();
}

void setData(Commands cmd, uint8_t target, int data) {
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write((uint8_t)cmd);
  Wire.write((uint8_t)target);
  Wire.write((uint8_t*)&data, 4);
  Wire.endTransmission();
}

int getData(Commands cmd, uint8_t target, uint8_t* buf) {
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write((uint8_t)cmd);
  Wire.write((uint8_t)target);
  Wire.endTransmission();

  Wire.requestFrom(I2C_ADDRESS, 5);
  uint8_t status =  Wire.read();
  if (status != 0) {
    controller.irq_status = status;
  }

  int i = 0;
  while (Wire.available()) {
    buf[i++] = (uint8_t)Wire.read();
  }
  return i;
}

int getData(Commands cmd, uint8_t* buf) {
  return getData(cmd, 0, buf);
}
}

mc::MotorController controller;

mc::ServoMotor servo1;
mc::ServoMotor servo2;
mc::ServoMotor servo3;
mc::ServoMotor servo4;

mc::DCMotor M1;
mc::DCMotor M2;
d21::DCMotor M3;
d21::DCMotor M4;

mc::Encoder encoder1;
mc::Encoder encoder2;

mc::PID pid1;
mc::PID pid2;

mc::Battery battery;

