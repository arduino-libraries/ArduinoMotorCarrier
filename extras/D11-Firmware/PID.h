#ifndef __PID_H__
#define __PID_H__

#include "src/FpF.hpp"
#include "src/PID/PID_v1.h"
#include "DCMotor.h"

#define Fix16 mn::MFixedPoint::FpF32<8>

typedef enum {
  CL_OPEN_LOOP = 0,
  CL_POSITION,
  CL_VELOCITY,
} cl_control;

typedef enum {
  TARGET_VELOCITY = 0,
  TARGET_POSITION
} cl_target;

class PIDWrapper {

  public:
    PIDWrapper(Fix16& inputpos, Fix16& inputvelo, DCMotor* motor, int index, int periodms_pos, int periodms_velo);

    void setGains(Fix16 kp, Fix16 ki, Fix16 kd) {
      if (this->mode == CL_VELOCITY) {
        pid_velo->SetTunings(kp, ki, kd);
      }
      if (this->mode == CL_POSITION) {
        pid_pos->SetTunings(kp, ki, kd);
      }
      run();
    };

    void resetGains();


    void getGains(Fix16* gains) {
      if (this->mode == CL_VELOCITY) {
        gains[0] = pid_velo->GetKp();
        gains[1] = pid_velo->GetKi();
        gains[2] = pid_velo->GetKd();
      }
      if (this->mode == CL_POSITION) {
        gains[0] = pid_pos->GetKp();
        gains[1] = pid_pos->GetKi();
        gains[2] = pid_pos->GetKd();
      }
    };

    void setControlMode(cl_control mode) {
      this->mode = mode;
      run();
    };

    void setSetpoint(cl_target control_target, Fix16 target) {
      if (control_target == TARGET_VELOCITY) {
        this->targetvelo = target;
      } else if (control_target == TARGET_POSITION) {
        this->targetpos = target;
      }
      run();
    };

    void setMaxAcceleration(Fix16 maxAccel) {
      this->maxAcceleration = maxAccel;
      run();
    };

    void setMaxVelocity(Fix16 maxVelocity) {
      this->maxVelocity = maxVelocity;
      run();
    };

    void setLimits(int16_t minDuty, int16_t maxDuty) {
      if (mode == CL_POSITION) {
        pid_pos->SetOutputLimits(Fix16(minDuty), Fix16(maxDuty));
      }
      if (mode == CL_VELOCITY) {
        pid_velo->SetOutputLimits(Fix16(minDuty), Fix16(maxDuty));
      }
      run();
    };

    void run() {
      pid_velo->SetMode(AUTOMATIC);
      pid_pos->SetMode(AUTOMATIC);
    };

    void stop() {
      pid_velo->SetMode(MANUAL);
      pid_pos->SetMode(MANUAL);
    };

    cl_control mode = CL_VELOCITY;
    Fix16 targetpos = 0.0;
    Fix16 targetvelo = 0.0;
    Fix16 maxAcceleration;
    Fix16 maxVelocity;
    int maxDuty = 100;
    int minDuty = 0;
    Fix16 actualDuty;
    Fix16 velocmd = 0.0f;
    PID* pid_velo;
    PID* pid_pos;
    DCMotor* motor;
    bool disabled = true;
};

#endif
