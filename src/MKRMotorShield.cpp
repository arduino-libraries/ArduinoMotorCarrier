#include "MKRMotorShield.h"

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
  mc::irq_status = Wire.read();

  int i = 0;
  while (Wire.available()) {
    buf[i++] = (uint8_t)Wire.read();
  }
  return i;
}

int getData(Commands cmd, uint8_t* buf) {
  return getData(cmd, 0, buf);
}
