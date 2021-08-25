/*
 * MakeBlock mBot
 * mCore control board (ATmega328) ~ Arduino Uno
 * 
 * Simple program to drive mBot in forward direction
 * 
 * Controls of motor speed and direction directly through pins D4 - D7
 * "MeMCore.h" library not required
 */


/*
 * Declare and initiate variables to control motor speed and direction
 * Motor connector M1 uses D6 for PWM (speed) and D7 for direction (HIGH = "+" or forward, LOW = "-" or reverse)
 * Motor connector M2 uses D5 for PWM (speed) and D4 for direction (HIGH = "+" or forward, LOW = "-" or reverse)
 * 
 * D6 and D7 are also Output compare (OC) pins that use a timestamp in memory to trigger a PWM output signal
 */

int rightMotorDir = 4;  //D4 <--> digitalWrite
int rightMotorSpeed = 5;  //D5 = OC0B:PWM <--> analogWrite
int leftMotorSpeed = 6; //D6 = OC0A:PWM <--> analogWrite
int leftMotorDir = 7; //D7 <--> digitalWrite

unsigned int motorSpeed = 150;  //PWM value in range [0, 255], where 0 = 0% and 255 = 100% duty cycle

void setup() {
  //declare board inputs and outputs (I/O)
  pinMode(rightMotorDir, OUTPUT);
  pinMode(rightMotorSpeed, OUTPUT);
  pinMode(leftMotorDir, OUTPUT);
  pinMode(leftMotorSpeed, OUTPUT);
}

void loop() {
  //Drive forward
  digitalWrite(rightMotorDir, HIGH);
  analogWrite(rightMotorSpeed, motorSpeed);
  digitalWrite(leftMotorDir, LOW);  //right and left motor are mirror-mounted; neg. speed is forward for left motor
  analogWrite(leftMotorSpeed, motorSpeed);
  
  delay(2000); //mBot will drive forward for "x" number of ms.
  
  //Stop
  analogWrite(rightMotorSpeed, 0);
  analogWrite(leftMotorSpeed, 0);

  
  //exit(0) --> stops the program running, but leaves the CPU running in an infinite loop;
  cli(); //disable interrupts
  while(1); //forever loop
}
