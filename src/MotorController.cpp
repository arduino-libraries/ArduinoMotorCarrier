/*
  MotorCOntroller.cpp - Library for Arduino Motor Carriers
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

#include "MotorController.h"
#include "Common.h"
#include "Wire.h"

#define PMIC_ADDRESS  0x6B
#define PMIC_REG00    0x00
#define PMIC_REG01    0x01
#define PMIC_REG02    0x02
#define PMIC_REG04    0x04
#define PMIC_REG05    0x05

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

  // PMIC initialization raw APIs: are used to initialize the
  // PMIC when used with Nano 33 IoT
#ifdef ARDUINO_SAMD_NANO_33_IOT
   Serial.println("Board: Nano 33 IoT");
   enable_battery_charging();
   Serial.println("Charging enabled....");
#endif
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

void mc::MotorController::enable_battery_charging() {
  Wire.beginTransmission(PMIC_ADDRESS);
  Wire.write(PMIC_REG00);
  Wire.write(0x06); // min sys voltage 3.88 V + max input current 2.0 A
  Wire.endTransmission();
  Wire.beginTransmission(PMIC_ADDRESS);
  Wire.write(PMIC_REG01);
  Wire.write(0x1B); // Charge Battery + Minimum System Voltage 3.5 V
  Wire.endTransmission();
  Wire.beginTransmission(PMIC_ADDRESS);
  Wire.write(PMIC_REG02);
  Wire.write(0x00); // Charge current  512 mA
  Wire.endTransmission();
  Wire.beginTransmission(PMIC_ADDRESS);
  Wire.write(PMIC_REG04);
  Wire.write(0x9E); // Charge Voltage Limit 4.128 V
  Wire.endTransmission();
  Wire.beginTransmission(PMIC_ADDRESS);
  Wire.write(PMIC_REG05);
  Wire.write(0x8A); // Enable Battery Charge termination + disable watchdog
  Wire.endTransmission();
}
