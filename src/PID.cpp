/*
  PID.cpp - Library for Arduino Motor Shields
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

#include "PID.h"
#include "Common.h"

namespace mc {
static int next_instance = 0;

PID::PID() {
  instance = next_instance;
  next_instance++;
}

void PID::setGains(int16_t kp, int16_t ki, int16_t kd) {
  setDataPIDGains(SET_PID_GAIN_CL_MOTOR, instance, kp, ki, kd);
}

void PID::resetGains() {
  setData(RESET_PID_GAIN_CL_MOTOR, instance, 0);
}

void PID::setControlMode(cl_control mode) {
  setData(SET_CONTROL_MODE_CL_MOTOR, instance, mode);
}

void PID::setSetpoint(cl_target control_target, int target) {
  if (control_target == TARGET_POSITION) {
    setData(SET_POSITION_SETPOINT_CL_MOTOR, instance, target);
  }
  if (control_target == TARGET_VELOCITY) {
    setData(SET_VELOCITY_SETPOINT_CL_MOTOR, instance, target);
  }
}

void PID::setMaxAcceleration(int maxAccel) {
  setData(SET_MAX_ACCELERATION_CL_MOTOR, instance, maxAccel);
}

void PID::setMaxVelocity(int maxVelocity) {
  setData(SET_MAX_VELOCITY_CL_MOTOR, instance, maxVelocity);
}

void PID::setLimits(int16_t minDuty, int16_t maxDuty) {
  setData(SET_MIN_MAX_DUTY_CYCLE_CL_MOTOR, instance, (minDuty << 16 | maxDuty));
}
}

namespace d21 {
static int next_instance = 0;

static float KP_DEFAULT = 5000.0f;
static float KI_DEFAULT = 100.0f;
static float KD_DEFAULT = 0.0f;

PID::PID(mc::Encoder& encoder, DCMotor& motor, int index, int periodms_velo , int periodms_pos) {
  instance = next_instance;
  next_instance++;
  pid_pos = new std::PID(&inputpos, &velocmd, &targetpos, KP_DEFAULT, KI_DEFAULT, KD_DEFAULT, DIRECT);
  pid_velo = new std::PID(&inputvelo, &actualDuty, &targetvelo, KP_DEFAULT, KI_DEFAULT, KD_DEFAULT, DIRECT);
  pid_pos->SetSampleTime(periodms_pos);
  pid_velo->SetSampleTime(periodms_velo);
  pid_pos->SetOutputLimits((short) - 30, (short)30); //position pid can only command +/- max_velo
  pid_velo->SetOutputLimits((short) - 100, (short)100); //velocity pid can only command +/- 100 PWM duty cycle
  this->motor = &motor;
  this->encoder = &encoder;
}

void PID::setGains(float kp, float ki, float kd) {
  pid_pos->SetTunings(kp, ki, kd);
  pid_velo->SetTunings(kp, ki, kd);
}

void PID::resetGains() {
  pid_pos->SetTunings(KP_DEFAULT, KI_DEFAULT, KD_DEFAULT);
  pid_velo->SetTunings(KP_DEFAULT, KI_DEFAULT, KD_DEFAULT);
}

void PID::setControlMode(cl_control mode) {
  this->mode = mode;
}

void PID::setSetpoint(cl_target control_target, int16_t target) {
  if (control_target == TARGET_VELOCITY) {
    this->targetvelo = target;
  } else if (control_target == TARGET_POSITION) {
    this->targetpos = target;
  }
}

void PID::setMaxAcceleration(int16_t maxAccel) {
  this->maxAcceleration = maxAccel;
}

void PID::setMaxVelocity(int16_t maxVelocity) {
  this->maxVelocity = maxVelocity;
}

void PID::setLimits(int16_t minDuty, int16_t maxDuty) {
  this->maxDuty = maxDuty;
  this->minDuty = minDuty;
}
}
