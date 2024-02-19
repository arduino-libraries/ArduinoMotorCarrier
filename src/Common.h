/*
  Common.h - Library for Arduino Motor Carriers
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

#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_GENERIC_STM32H747_M4)
#define RESET _RESET
#endif

enum Commands {
  GET_VERSION = 0x01,
  RESET,
  SET_PWM_DUTY_CYCLE_SERVO,
  SET_PWM_FREQUENCY_SERVO,
  SET_PWM_DUTY_CYCLE_DC_MOTOR,
  SET_PWM_FREQUENCY_DC_MOTOR,
  GET_RAW_COUNT_ENCODER,
  RESET_COUNT_ENCODER,
  GET_OVERFLOW_UNDERFLOW_STATUS_ENCODER,
  GET_COUNT_PER_SECOND_ENCODER,
  SET_INTERRUPT_ON_COUNT_ENCODER,
  SET_INTERRUPT_ON_VELOCITY_ENCODER,
  GET_RAW_ADC_BATTERY,
  GET_CONVERTED_ADC_BATTERY,
  GET_FILTERED_ADC_BATTERY,
  SET_PID_GAIN_CL_MOTOR,
  RESET_PID_GAIN_CL_MOTOR,
  SET_CONTROL_MODE_CL_MOTOR,
  SET_POSITION_SETPOINT_CL_MOTOR,
  SET_VELOCITY_SETPOINT_CL_MOTOR,
  SET_MAX_ACCELERATION_CL_MOTOR,
  SET_MAX_VELOCITY_CL_MOTOR,
  SET_MIN_MAX_DUTY_CYCLE_CL_MOTOR,
  PING,
  GET_INTERNAL_TEMP,
  CLEAR_IRQ,
  GET_FREE_RAM,
  GET_PID_VAL
};

enum IRQCause {
  ENCODER_COUNTER_REACHED = 1,
  ENCODER_VELOCITY_REACHED,
};

#define I2C_ADDRESS   0x66
#define IRQ_PIN       6

#ifdef ARDUINO_SAMD_NANO_33_IOT
#define MOTOR_3_PIN_A 2
#define MOTOR_3_PIN_B 3
#define MOTOR_4_PIN_A 5
#define MOTOR_4_PIN_B 4
#else
#define MOTOR_3_PIN_A 3
#define MOTOR_3_PIN_B 2
#define MOTOR_4_PIN_A 4
#define MOTOR_4_PIN_B 5
#endif


#ifdef ARDUINO_SAMD_NANO_33_IOT
  #define IN1 A7
  #define IN2 A2
  #define IN3 A6
  #define IN4 A3
#else
  #define IN1 A6
  #define IN2 A1
  #define IN3 A5
  #define IN4 A2
#endif

#include "src/FpF.hpp"
#define Fix16 mn::MFixedPoint::FpF32<8>

namespace mc {
int getData(Commands cmd, uint8_t target, uint8_t* buf);
void setData(Commands cmd, uint8_t target, int data);
void setDataPIDGains(Commands cmd, uint8_t target, Fix16 P, Fix16 I, Fix16 D);
int getDataPIDGains(Commands cmd, uint8_t target, uint8_t* buf, int dataSize);
int getData(Commands cmd, uint8_t* buf);
}
