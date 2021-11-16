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

MeUltrasonicSensor ultrasonic(8); //ultra sonic sensor connected to RJ25 port 8

void setup(){
  
  Serial.begin(9600);
  
}

void loop(){
  
  Serial.print("Distance:  ");
  Serial.print(ultrasonic.distanceCm());
   
  if (ultrasonic.distanceCm() < 18){
    Serial.println("     Collision Imminent!!");
  }
  else if ((ultrasonic.distanceCm() < 25) && (ultrasonic.distanceCm() > 18)){
    Serial.println("     Collision Warning!");
  }
  else{
    Serial.println("     Clear");
  }

}
