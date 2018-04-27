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
