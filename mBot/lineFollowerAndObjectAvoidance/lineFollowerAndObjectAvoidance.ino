/*
 * lineFollowerAndObjectAvoidance
 * 
 * Combination and modification of the lineFollow and ObstacleAvoidance examples.
 * Once the onboard button is pressed the mBot will search for and follow a black line.
 * If an obstacle is detected. The mBot will reverse, turn, and resume seaching for and 
 * following the black line.
 * 
 * The circuit:
 *  - line follow sensor connected to port 2
 *  - ultra sonic sensor connected to port 3
 *
 * created 2 sep 2020
 * by Colin Vinson
 * modified 12 sep 2021
*/

#include <MeMCore.h>

MeDCMotor motorLeft(M1);  
MeDCMotor motorRight(M2);

MeLineFollower lineFollower(2); //line follower
MeUltrasonicSensor ultraSensor(3);

uint8_t moveSpeed = 150;
float lineDirIndex = 10;
float dist;

#define button A7 //onboard button is connected to analog pin A7

void setup() {
  Serial.begin(9600); 
}

void loop() {
  while(analogRead(button) < 10){ //default button state is HIGH (1023)
    while (true){
      dist = ultraSensor.distanceCm();
      Serial.println(dist);
      
      if(dist < 10 && dist > 1)  {
        obstacleAvoidance();      
      } 
      else {
        lineFollow();  
      }
    }
  }
}

void lineFollow(){
  
  int sensorState = lineFollower.readSensors();
  Serial.println(sensorState);
  
  //lineFollower sensor less reliable at full speed
  if(moveSpeed > 200) {
    moveSpeed = 200;
  }
  switch(sensorState)
  {
    case 0: 
      //Serial.println("Sensor 1 and 2 are inside of black line"); 
      forward(); // forward    
      lineDirIndex = 10;
      break;
    case 1: 
      //Serial.println("Sensor 2 is outside of black line"); 
      forward(); // forward    
      if(lineDirIndex > 1) {
        lineDirIndex--;
      }       
      break;
    case 2: 
      //Serial.println("Sensor 1 is outside of black line"); 
      forward(); // forward
      if(lineDirIndex < 20){
        lineDirIndex++;
      }     
      break;
    case 3: 
      //Serial.println("Sensor 1 and 2 are outside of black line"); 
      if(lineDirIndex == 10){
        reverse(); // reverse
      }
      if(lineDirIndex == 10.5){
        motorLeft.run(-moveSpeed); // Turn right
        motorRight.run(moveSpeed/1.8);
      }
      if(lineDirIndex < 10){
        turnLeft(); // Turn left
      }
      if(lineDirIndex > 10.5){
        turnRight(); // Turn right
      }            
      break;
  }
}

void obstacleAvoidance() {
  reverse();
  delay(150);
  turnLeft();
  //motorLeft.run(moveSpeed); // Turn left
  //motorRight.run(moveSpeed);
  delay(450);
  lineDirIndex = 10.5;
}

void forward()
{
  motorLeft.run(-moveSpeed);
  motorRight.run(moveSpeed);
}
void reverse()
{
  motorLeft.run(moveSpeed);
  motorRight.run(-moveSpeed);
}
void turnLeft()
{
  motorLeft.run(-moveSpeed/10); // Turn left
  motorRight.run(moveSpeed);
}
void turnRight()
{
  motorLeft.run(-moveSpeed); // Turn right
  motorRight.run(moveSpeed/10);
}
void Stop()
{
  motorLeft.run(0);
  motorRight.run(0);
}
