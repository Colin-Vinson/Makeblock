/*
 * MeMegaPi_ServoTest
 * 
 * Simple program to test the use of the Servo.h library with the MegaPi
 * 
 */

//Include Servo library: 
//MeMegaPi.h has it's own copy of Servo.h under Makeblock-Libraries-master>src>utility
//Chose either MeMegaPi.h or Servo.h
#include <MeMegaPi.h> 
//#include <Servo.h>

Servo meServo; //create servo object to control a servo with the functions provided by the library

void setup(){
    meServo.attach(63); //pins A6 - A15 = pins 60 - 69 (port 6 = pins 62 and 63)
}                       //when using the RJ25 adapter, slot-1 = pin 62 and slot-2 = pin 63

void loop(){
  meServo.write(90); //input desired angle from 0 - 180 degrees
  delay(30); //gives time for the motor to travel
}
