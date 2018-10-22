/*
  Common.h - Library for Arduino MKR Motor Shield
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
};

enum IRQCause {
  ENCODER_COUNTER_REACHED = 1,
  ENCODER_VELOCITY_REACHED,
};

#define I2C_ADDRESS   0x66
#define IRQ_PIN       6

#define MOTOR_3_PIN_A 3
#define MOTOR_3_PIN_B 2
#define MOTOR_4_PIN_A 4
#define MOTOR_4_PIN_B 5

#define IN1 A6
#define IN2 A1
#define IN3 A5
#define IN4 A2

namespace mc {
int getData(Commands cmd, uint8_t target, uint8_t* buf);
void setData(Commands cmd, uint8_t target, int data);
void setDataPIDGains(Commands cmd, uint8_t target, int16_t P, int16_t I, int16_t D);
int getData(Commands cmd, uint8_t* buf);
}
