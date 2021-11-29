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

float disFront;
float disRight;
float disLeft;

Servo meServo; //create servo object to control a servo with the functions provided by the library
int servoDelay = 400;

void setup(){
  Serial.begin(9600);

  meServo.attach(63); //port 6 slot 2 (A9 = D63 on Arduino Mega)
  
}

void loop(){
  disFront = ultrasonic.distanceCm();

  if (disFront < 10){
    evalRight();
    evalLeft();
    servoFront();
  }
  Serial.print("Front: ");
  Serial.print(disFront);
  Serial.print("Right: ");
  Serial.print(disRight);
  Serial.print("Left: ");
  Serial.println(disLeft);
}

void servoFront(){
  meServo.write(90);
  delay(servoDelay);
}

void evalRight(){
   meServo.write(0);
   delay(servoDelay);
   disRight = ultrasonic.distanceCm();
   delay(servoDelay);
}

void evalLeft(){
  meServo.write(180);
  delay(servoDelay);
  disLeft = ultrasonic.distanceCm();
  delay(servoDelay);
}
