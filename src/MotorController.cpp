#include "MotorController.h"
#include "Common.h"

String mc::MotorController::getFWVersion() {
  char ret[5];
  getData(GET_VERSION, (uint8_t*)ret);
  ret[4] = '\0';
  return String(ret);
}

void mc::MotorController::reboot() {
  setData(RESET, 0, 0);
}

void mc::MotorController::ping() {
  setData(PING, 0, 0);
}

float mc::MotorController::getTemperature() {
  int ret;
  getData(GET_INTERNAL_TEMP, (uint8_t*)&ret);
  return (float)ret / 1000.0f;
}
