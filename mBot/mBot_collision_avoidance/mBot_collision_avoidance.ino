/*
 * MakeBlock mBot
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

#include <MeMCore.h>

MeUltrasonicSensor ultrasonic(3); //ultra sonic sensor connected to RJ25 port 3

MeRGBLed rgbLed(7, 2);  //MeRGBLed(port, led#): onboard rgb leds connected to D13 = port 7

MeBuzzer buzzer;

void setup(){
  //fill the LED color data to pixels_bak
  rgbLed.fillPixelsBak(0, 2, 1);

  Serial.begin(9600);

}

void loop(){
  
  Serial.print("Distance:  ");
  Serial.print(ultrasonic.distanceCm());
   
  if (ultrasonic.distanceCm() > 15){
    rgbLed.setColor(0,0,255,0);  //setColor(index, red, green, blue): index 0, all the LED will be lit 
    rgbLed.show();
    
    buzzer.noTone();

    Serial.println("     Clear");
  }
  else if ((ultrasonic.distanceCm() < 15) && (ultrasonic.distanceCm() > 7)){
    rgbLed.setColor(0,255,255,0);
    rgbLed.show();
    
    buzzer.tone(523, 10*ultrasonic.distanceCm());  //523Hz = C_5
    delay(10*ultrasonic.distanceCm());

    Serial.println("     Collision Warning!");
  }
  else{
    rgbLed.setColor(0,255,0,0);
    rgbLed.show();

    buzzer.tone(1047, 10*ultrasonic.distanceCm()); //1047 = C_6
    delay(10*ultrasonic.distanceCm());

    Serial.println("     Collision Imminent!!");
  }

}
