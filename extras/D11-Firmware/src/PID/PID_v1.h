#ifndef PID_v1_h
#define PID_v1_h
#define LIBRARY_VERSION	1.2.1

#include "../FpF.hpp"

#define Fix16 	mn::MFixedPoint::FpF32<8>

class PID
{


  public:

  //Constants used in some of the functions below
  #define AUTOMATIC	1
  #define MANUAL	0
  #define DIRECT  0
  #define REVERSE  1
  #define P_ON_M 0
  #define P_ON_E 1

  //commonly used functions **************************************************************************
    PID(Fix16*, Fix16*, Fix16*,        // * constructor.  links the PID to the Input, Output, and 
        Fix16, Fix16, Fix16, int, int);//   Setpoint.  Initial tuning parameters are also set here.
                                          //   (overload for specifying proportional mode)

    PID(Fix16*, Fix16*, Fix16*,        // * constructor.  links the PID to the Input, Output, and 
        Fix16, Fix16, Fix16, int);     //   Setpoint.  Initial tuning parameters are also set here
	
    void SetMode(int Mode);               // * sets PID to either Manual (0) or Auto (non-0)

    bool Compute();                       // * performs the PID calculation.  it should be
                                          //   called every time loop() cycles. ON/OFF and
                                          //   calculation frequency can be set using SetMode
                                          //   SetSampleTime respectively

    void SetOutputLimits(Fix16, Fix16); // * clamps the output to a specific range. 0-255 by default, but
										                      //   it's likely the user will want to change this depending on
										                      //   the application
	


  //available but not commonly used functions ********************************************************
    void SetTunings(Fix16, Fix16,       // * While most users will set the tunings once in the 
                    Fix16);         	    //   constructor, this function gives the user the option
                                          //   of changing tunings during runtime for Adaptive control
    void SetTunings(Fix16, Fix16,       // * overload for specifying proportional mode
                    Fix16, int);         	  

	void SetControllerDirection(int);	  // * Sets the Direction, or "Action" of the controller. DIRECT
										  //   means the output will increase when error is positive. REVERSE
										  //   means the opposite.  it's very unlikely that this will be needed
										  //   once it is set in the constructor.
    void SetSampleTime(int);              // * sets the frequency, in Milliseconds, with which 
                                          //   the PID calculation is performed.  default is 100
										  
										  
										  
  //Display functions ****************************************************************
	Fix16 GetKp();						  // These functions query the pid for interal values.
	Fix16 GetKi();						  //  they were created mainly for the pid front-end,
	Fix16 GetKd();						  // where it's important to know what is actually 
	int GetMode();						  //  inside the PID.
	int GetDirection();					  //

  private:
	void Initialize();
	
	Fix16 dispKp;				// * we'll hold on to the tuning parameters in user-entered 
	Fix16 dispKi;				//   format for display purposes
	Fix16 dispKd;				//
    
	Fix16 kp;                  // * (P)roportional Tuning Parameter
    Fix16 ki;                  // * (I)ntegral Tuning Parameter
    Fix16 kd;                  // * (D)erivative Tuning Parameter

	int controllerDirection;
	int pOn;

    Fix16 *myInput;              // * Pointers to the Input, Output, and Setpoint variables
    Fix16 *myOutput;             //   This creates a hard link between the variables and the 
    Fix16 *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                  //   what these values are.  with pointers we'll just know.
			  
	unsigned long lastTime;
	Fix16 outputSum, lastInput;
	Fix16 lastError;
	Fix16 iError; //integral error

	unsigned long SampleTime;
	Fix16 outMin, outMax;
	bool inAuto, pOnE;
};
#endif

