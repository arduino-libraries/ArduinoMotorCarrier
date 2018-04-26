#include "MKRMotorShield.h"

const int pingPin = IN4;
const byte interruptPin = IN2;

long encoderResetValue = 5;

mc::MotorController controller;

mc::ServoMotor servo1 = mc::ServoMotor();
mc::ServoMotor servo2 = mc::ServoMotor();
mc::ServoMotor servo3 = mc::ServoMotor();
mc::ServoMotor servo4 = mc::ServoMotor();

mc::DCMotor M2 = mc::DCMotor();
mc::DCMotor M1 = mc::DCMotor();
d21::DCMotor M3 = d21::DCMotor();
d21::DCMotor M4 = d21::DCMotor();

mc::Encoder encoder2 = mc::Encoder();
mc::Encoder encoder1 = mc::Encoder();

mc::PID pid2 = mc::PID();
mc::PID pid1 = mc::PID();

volatile uint8_t irq_status;

void getDataIrq() {
  irq_status = 1;
};

int m2_pos = 0;
//boolean toggle1 = false;
//boolean toggle2 = false;

void setup() {
  
  Serial.begin(115200);
  while (!Serial);
  // create mkrshield connection
  Wire.begin();
  
  delay(500);

  //create encoder2 object in MATLAB
  pinMode(IRQ_PIN, INPUT_PULLUP);
  attachInterrupt(IRQ_PIN, getDataIrq, FALLING);  
  encoder2.resetCounter(0); 
  
// create dcmotor2 object in matlab
  M2.setFrequency(100);  

  // enable dc motor2 object

  M2.setDuty(90);

  while(m2_pos < 36000){
    m2_pos = encoder2.getRawCount();
    controller.ping();
  }
  Serial.println(m2_pos);
  //M2.setDuty(0);   
  pid2.setControlMode(CL_POSITION);
  pid2.setGains(25, 0, 3);
  pid2.setMaxAcceleration(4000); 
  controller.ping();
  delay(1000);
  pid2.setSetpoint(TARGET_POSITION, 10000);
}
void loop() {
  m2_pos = encoder2.getRawCount();
  Serial.println(m2_pos);
  controller.ping();
}
