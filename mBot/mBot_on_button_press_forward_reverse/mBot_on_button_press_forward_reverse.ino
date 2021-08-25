/*
 * MakeBlock mBot
 * mCore control board (ATmega328) ~ Arduino Uno
 * 
 * Program to drive mBot forward and reverse after onboard button press
 * 
 * Controls of motor speed and direction using MeMCore library motor control functions
 */
#include "MeMCore.h"

/*
 * Motor connector M1 uses D6 for PWM (speed) and D7 for direction (HIGH = "+" or forward, LOW = "-" or reverse)
 * Motor connector M2 uses D5 for PWM (speed) and D4 for direction (HIGH = "+" or forward, LOW = "-" or reverse)
 */
MeDCMotor motorLeft(M1);  //Left motor connected to M1 motor connector
MeDCMotor motorRight(M2); //Right motor connected to M2 motor connecetor

uint8_t motorSpeed = 100; //value: between 0 and 255 for PWM output, "uint8_t" = unsigned integer of length 8 bits

#define button A7 //onboard button is connected to analog pin A7

void setup(){
  //declare board inputs and outputs (I/O)
  pinMode(button, INPUT);

  //sets data/baud rate (bits per second) for communicating with serial monitor
  Serial.begin(9600);
}

void loop(){
  while(analogRead(button) < 10){ //default button state is HIGH (1023)

    //Forward
    motorLeft.run(-motorSpeed); //right and left motor are mirror-mounted; neg. speed is forward for left motor
    motorRight.run(motorSpeed); 
    delay(2000);
    
    //Stop
    motorLeft.stop();
    motorRight.stop();
    delay(100);
    
    //Reverse
    motorLeft.run(motorSpeed);
    motorRight.run(-motorSpeed);
    delay(2000);
    
    //Stop
    motorLeft.stop();
    motorRight.stop();
    delay(2000);
    
  }
  Serial.println(analogRead(button));
}
