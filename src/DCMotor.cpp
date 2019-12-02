/*
  DCMotor.cpp - Library for Arduino Motor Shields
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

#include "DCMotor.h"
#include "Common.h"

namespace mc {
static int next_instance = 0;

DCMotor::DCMotor() {
  instance = next_instance;
  next_instance++;
};

void DCMotor::setDuty(int duty) {
  setData(SET_PWM_DUTY_CYCLE_DC_MOTOR, instance, duty);
}

void DCMotor::setFrequency(int frequency) {
  setData(SET_PWM_FREQUENCY_DC_MOTOR, instance, frequency);
}

}
// D21 implementations

namespace d21 {
static int next_instance = 0;

DCMotor::DCMotor() {
  instance = next_instance;
  next_instance++;
  if (instance == 0) {
    in1 = MOTOR_3_PIN_A; //2;
    in2 = MOTOR_3_PIN_B; //3;
  } else {
    in1 = MOTOR_4_PIN_A; //5;
    in2 = MOTOR_4_PIN_B; //4;
  }
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
};

void DCMotor::setDuty(int duty) {
  //setData(SET_PWM_DUTY_CYCLE_DC_MOTOR, instance, duty);
  this->duty = duty;
  if (duty == 0) {
    analogWrite(in1, 0);
    analogWrite(in2, 0);
    return;
  }
  if (duty > 0) {
    analogWrite(in1, 0);
    analogWrite(in2, map(duty, 0, 100, 0, 255));
  } else {
    analogWrite(in2, 0);
    analogWrite(in1, map(-duty, 0, 100, 0, 255));
  }

}

void DCMotor::setFrequency(int frequency) {
  //setData(SET_PWM_FREQUENCY_DC_MOTOR, instance, frequency);
}
}
