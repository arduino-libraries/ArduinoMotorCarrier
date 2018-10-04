/*
  MotorCOntroller.cpp - Library for Arduino MKR Motor Shield
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

#include "MotorController.h"
#include "Common.h"
#include "Wire.h"

String mc::MotorController::getFWVersion() {
  char ret[5];
  getData(GET_VERSION, (uint8_t*)ret);
  ret[4] = '\0';
  return String(ret);
}

void mc::MotorController::reboot() {
  setData(RESET, 0, 0);
  delay(500);
}

void mc::MotorController::ping() {
  setData(PING, 0, 0);
}

float mc::MotorController::getTemperature() {
  int ret;
  getData(GET_INTERNAL_TEMP, (uint8_t*)&ret);
  return (float)ret / 1000.0f;
}

int mc::MotorController::begin() {
  Wire.begin();
  String version = getFWVersion();
  if (version.c_str()[0] == '0') {
    return 1;
  }
  return 0;
};

uint8_t mc::MotorController::getIrqStatus() {
  int ret;
  getData(CLEAR_IRQ, (uint8_t*)&ret);
  return irq_status;
}

int mc::MotorController::getFreeRam() {
  int ret;
  getData(GET_FREE_RAM, (uint8_t*)&ret);
  return ret;
}