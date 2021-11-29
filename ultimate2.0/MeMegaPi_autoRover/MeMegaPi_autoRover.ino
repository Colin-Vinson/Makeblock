/*
 * MakeBlock Ultimate 2.0
 * mCore control board (ATmega328) ~ Arduino Uno
 * 
 * Collision avoidance:
 *
 * The ultrasonic sensor will measure the distance in front of the mBot. 
 * The onboard RGB leds will change from green to yellow to red as the mBot nears an obstacle.
 * The onboard buzzer will play a tone in increasing periodicity and frequency as the mBot nears the obstacle.
 * 
 * libraries:
 * MeMCore.h main mBot library
 * 
 * drivers:
 * MeUltrasonicSensor.h to control the ultrasonic sensor module
 * MeRGBLed.h to control the two onboard WS2812 RGB Leds
 * MeBuzzer.h library to control the onboard buzzer
 */

#include <MeMegaPi.h>

MeUltrasonicSensor ultrasonic(7); //ultra sonic sensor connected to RJ25 port 8
float distFront;
float distRight;
float distLeft;

Servo meServo; //create servo object to control a servo with the functions provided by the library
int servoDelay = 400;

MeMegaPiDCMotor motorR(PORT1B); //right motor
MeMegaPiDCMotor motorL(PORT2B); //left motor
int motorSpeed = 255; //PWM value 0 - 255 (0 - 100% motor speed)
int turnDelay = 850;  //millisecond delay to turn rover 90 degrees

void setup(){
  Serial.begin(9600);

  meServo.attach(63); //port 6 slot 2 (A9 = D63 on Arduino Mega)
}

void loop(){
  distFront = ultrasonic.distanceCm();

  if (distFront < 10){
    evalRight();
    evalLeft();
    servoFront();
    if (distRight > distLeft){
      turnRight();
    }
    else if (distLeft > distRight){
      turnLeft();
    }
  }
  
  Serial.print("Front: ");
  Serial.print(distFront);
  Serial.print("Right: ");
  Serial.print(distRight);
  Serial.print("Left: ");
  Serial.println(distLeft);
}

void forward(){
  motorR.run(-motorSpeed);
  motorL.run(motorSpeed);
}

void turnRight(){
  motorR.run(motorSpeed);
  motorL.run(motorSpeed);
  delay(turnDelay);
  motorR.stop();
  motorL.stop();
}

void turnLeft(){
  motorR.run(-motorSpeed);
  motorL.run(-motorSpeed);
  delay(turnDelay);
  motorR.stop();
  motorL.stop();
}

void roverStop(){
  motorR.stop();
  motorL.stop();
}

void servoFront(){
  meServo.write(90);
  delay(servoDelay);
}

void evalRight(){
   meServo.write(0);
   delay(servoDelay);
   distRight = ultrasonic.distanceCm();
   delay(servoDelay);
}

void evalLeft(){
  meServo.write(180);
  delay(servoDelay);
  distLeft = ultrasonic.distanceCm();
  delay(servoDelay);
}
