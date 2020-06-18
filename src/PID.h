#ifndef __PID_H__
#define __PID_H__

#include "Arduino.h"
#include "DCMotor.h"
//-------------------------------- ----------------------
#include "src/FpF.hpp"
#define Fix16 mn::MFixedPoint::FpF32<8>
//------------------------------------------------------

typedef enum {
  CL_OPEN_LOOP = 0,
  CL_POSITION,
  CL_VELOCITY,
} cl_control;

typedef enum {
  TARGET_VELOCITY = 0,
  TARGET_POSITION
} cl_target;

namespace mc {

class PID {

  public:
    PID();

    void setGains(Fix16 kp, Fix16 ki, Fix16 kd);
    void resetGains();
    void setControlMode(cl_control mode);
    void setSetpoint(cl_target control_target, int target);
    void setMaxAcceleration(int maxAccel);
    void setMaxVelocity(int maxVelocity);
    void setLimits(int16_t minDuty, int16_t maxDuty);
    Fix16 getPgain();
    Fix16 getIgain();
    Fix16 getDgain();

  private:
    int instance;
};
}

#include "src/PID/PID_v1.h"
#include "Encoder.h"

namespace d21 {
class PID {

  public:
    PID(mc::Encoder& encoder, DCMotor& motor, int index, int periodms_velo , int periodms_pos);

    void setGains(float kp, float ki, float kd);
    void setGains(int16_t kp, int16_t ki, int16_t kd) {
      setGains((float)kp, (float)ki, (float)kd);
    }
    void resetGains();
    void setControlMode(cl_control mode);
    void setSetpoint(cl_target control_target, int16_t target);
    void setMaxAcceleration(int16_t maxAccel);
    void setMaxVelocity(int16_t maxVelocity);
    void setLimits(int16_t minDuty, int16_t maxDuty);

    void run() {
      pid_velo->SetMode(AUTOMATIC);
      pid_pos->SetMode(AUTOMATIC);
    };

    /* ATTENTION: d21::PID::update() should be called very often */
    void update() {

      inputpos = (float)encoder->getRawCount();
      inputvelo = (float)encoder->getCountPerSecond();

      static float prevvelocmd = 0.0f;
      if (mode == CL_POSITION) {
        if (pid_pos->Compute()) {
          //slew limit velocity command with max accel
          float curvelocmd = velocmd;
          if ((prevvelocmd - curvelocmd) > maxAcceleration) curvelocmd = prevvelocmd - maxAcceleration;//limit decel
          if ((curvelocmd - prevvelocmd) > maxAcceleration) curvelocmd = prevvelocmd + maxAcceleration;//limit accel
          //copy position PID output to velocity PID setpoint
          targetvelo = curvelocmd;
          //save curvelocmd for next iteration
          prevvelocmd = curvelocmd;
        }
      }

      if (pid_velo->Compute()) {
        int dutyout = (int)actualDuty;
        //obj[i]->motor->setDuty(dutyout);  not working so using line below instead

        //deadzone compensation
        if (dutyout > 0) dutyout += 13; else dutyout -= 13;
        motor->setDuty(dutyout);
      }
    };

    void stop() {
      pid_velo->SetMode(MANUAL);
      pid_pos->SetMode(MANUAL);
    };

  private:
    int instance;
    cl_control mode = CL_VELOCITY;
    float targetpos = 0.0f;
    float targetvelo = 0.0f;
    float inputpos = 0.0f;
    float inputvelo = 0.0f;
    float maxAcceleration;
    float maxVelocity;
    int maxDuty = 100;
    int minDuty = 0;
    float actualDuty;
    float velocmd = 0.0f;
    std::PID* pid_velo;
    std::PID* pid_pos;
    DCMotor* motor;
    mc::Encoder* encoder;
};
}

#endif
