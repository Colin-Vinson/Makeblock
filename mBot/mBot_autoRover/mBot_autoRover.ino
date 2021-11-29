/*
 * @file    autoRover.ino
 * @author  Colin Vinson
 * @version V1.0.0
 * @date    18.10.2021
 * @brief   Description: autonomous tank with ultrasonic sensor and IR sensor (line follower)
 *
 */
#include "MeMegaPi.h"

MeUltrasonicSensor ultraSensor(PORT_8);

MeLineFollower lineFinder(PORT_5);

MeMegaPiDCMotor motor1(PORT1B);
MeMegaPiDCMotor motor2(PORT2B);

float distance;
int sensorState;
int motorSpeed = 255/2.5;

void setup()
{
  Serial.begin(9600);
}

void loop(){
  sensorState = lineFinder.readSensors();
  
  if (sensorState == S1_OUT_S2_OUT){
    drive();
  }
  else{
    stop();
  }
  
  delay(100);
}

void drive(){
  distance = ultraSensor.distanceCm();
  if (distance < 20){
    reverse(motorSpeed);
    delay(1000);
    turnRight(motorSpeed);
    delay(1000);
  }
  else{
    forward(motorSpeed);
  }
  Serial.println(distance);
}

void forward(int motorSpeed){
  motor1.run(-motorSpeed);
  motor2.run(motorSpeed);
}

void reverse(int motorSpeed){
  motor1.run(motorSpeed);
  motor2.run(-motorSpeed);
}

void turnRight(int motorSpeed){
  motor1.run(motorSpeed);
  motor2.run(motorSpeed);
}

void turnLeft(int motorSpeed){
  motor1.run(-motorSpeed);
  motor2.run(-motorSpeed);
}

void stop(void){
  motor1.stop();
  motor2.stop();
}
