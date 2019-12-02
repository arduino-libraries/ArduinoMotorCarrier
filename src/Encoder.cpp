/*
  Encoder.cpp - Library for Arduino Motor Shields
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

#include "Encoder.h"
#include "Wire.h"
#include "Common.h"

static int next_instance = 0;

mc::Encoder::Encoder() {
  instance = next_instance;
  next_instance++;
};

void mc::Encoder::resetCounter(long value) {
  setData(RESET_COUNT_ENCODER, instance, value);
}

int mc::Encoder::getRawCount() {
  int ret;
  getData(GET_RAW_COUNT_ENCODER, instance, (uint8_t*)&ret);
  return ret;
}

int mc::Encoder::getOverflowUnderflow() {
  uint8_t ret[2];
  getData(GET_OVERFLOW_UNDERFLOW_STATUS_ENCODER, instance, (uint8_t*)ret);
  return ret[0] << 8 | ret[1];
}

int mc::Encoder::getCountPerSecond() {
  int ret;
  getData(GET_COUNT_PER_SECOND_ENCODER, instance, (uint8_t*)&ret);
  return ret;
}

void mc::Encoder::setIrqOnCount(long value) {
  setData(SET_INTERRUPT_ON_COUNT_ENCODER, instance, value);
}

void mc::Encoder::setIrqOnVelocity(long value, uint8_t margin) {
  setData(SET_INTERRUPT_ON_VELOCITY_ENCODER, instance, (margin << 24 | value));
}
