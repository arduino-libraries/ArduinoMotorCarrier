#include "PID.h"
#include "Events.h"

static PIDWrapper* obj[2] = {NULL, NULL};

//extern DCMotor dcmotors[2];// necessary for workaround below

void calculatePID_wrapper(void* arg) {
  static Fix16 prevvelocmd[2] = {0.0f, 0.0f};

  for (int i = 0; i < 2; i++) {

    if (obj[i]->mode == CL_POSITION) {
      if (obj[i]->pid_pos->Compute()) {
        Fix16 curvelocmd = obj[i]->velocmd;
        //copy position PID output to velocity PID setpoint
        obj[i]->targetvelo = curvelocmd;
        //save curvelocmd for next iteration
        prevvelocmd[i] = curvelocmd;
        int dutyout = (int16_t)curvelocmd ;
        obj[i]->motor->setDuty(dutyout); //dutyout should be a value between -100 and 100.
      }
    } else {
      //CL_VELOCITY
      if (obj[i]->pid_velo->Compute()) {
        int dutyout = int32_t(obj[i]->actualDuty);
        obj[i]->motor->setDuty(dutyout);
      }
    }
  }
}

Fix16 KP_DEFAULT, KI_DEFAULT, KD_DEFAULT;

PIDWrapper::PIDWrapper(Fix16& inputpos, Fix16& inputvelo, DCMotor* motor, int index, int periodms_velo , int periodms_pos) {

  KP_DEFAULT = Fix16(2.0);
  KI_DEFAULT = Fix16(2.0);
  KD_DEFAULT = Fix16(0.0);

  pid_pos = new PID(&inputpos, &velocmd, &targetpos, KP_DEFAULT, KI_DEFAULT, KD_DEFAULT, DIRECT);
  pid_velo = new PID(&inputvelo, &actualDuty, &targetvelo, KP_DEFAULT, KI_DEFAULT, KD_DEFAULT, DIRECT);
  pid_pos->SetSampleTime(periodms_pos);
  pid_velo->SetSampleTime(periodms_velo);
  pid_pos->SetOutputLimits(Fix16(-30.0), Fix16(30.0)); //position pid can only command +/- max_velo
  pid_velo->SetOutputLimits(Fix16(-90.0), Fix16(90.0)); //velocity pid can only command +/- 100 PWM duty cycle

  stop();

  this->motor = motor;
  this->motor->pid = this;
  obj[index] = this;
  if (index == 0) {
    // recalculate every millisecond
    registerTimedEvent(calculatePID_wrapper, this, 0);
  }
}

void PIDWrapper::resetGains() {
  cl_control prev_mode = this->mode;
  this->mode = CL_VELOCITY;
  setGains(KP_DEFAULT, KI_DEFAULT, KD_DEFAULT);
  this->mode = CL_POSITION;
  setGains(KP_DEFAULT, KI_DEFAULT, KD_DEFAULT);
  this->mode = prev_mode;
  run();
};
