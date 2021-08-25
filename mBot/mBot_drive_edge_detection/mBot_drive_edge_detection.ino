#include <MeMCore.h>

MeLineFollower linefollower(2); //IR line follow sensor connected to port 2
MeDCMotor motorLeft9(M1);
MeDCMotor motorRight(M2);

int rightMotorDir = 4;  //D4 <--> digitalWrite
int rightMotorSpeed = 5;  //D5 = OC0B:PWM <--> analogWrite
int leftMotorSpeed = 6; //D6 = OC0A:PWM <--> analogWrite
int leftMotorDir = 7; //D7 <--> digitalWrite

#define button A7 //onboard button is connected to analog pin A7

int ldr;
int edgeDetect;

int randNumber;

int ldrValue = 1012;
int revSpeed = 200;
int revDuration = 1000;
int fwdSpeed = 150;

void setup() {
  Serial.begin(9600);

  //declare board inputs and outputs (I/O)
  pinMode(rightMotorDir, OUTPUT);
  pinMode(rightMotorSpeed, OUTPUT);
  pinMode(leftMotorDir, OUTPUT);
  pinMode(leftMotorSpeed, OUTPUT);

  randomSeed(analogRead(0));
}

void loop() { 
  while(analogRead(button) < 10){ //default button state is HIGH (1023)
    while (ldr < ldrValue){
      //read the light sensor and line follow sensor
      ldr = analogRead(A6); //onboard ldr connected to analog pin A6
      edgeDetect = linefollower.readSensors();  //0 = neither, 1 = right, 2 = left, 3 = both
      
      Serial.print(edgeDetect); 
      Serial.print("     ");
      Serial.println(ldr);
      if (edgeDetect == 0){
        reverse(revSpeed, revDuration);  //reverse(speed (0-255), reverse time (ms))
        randNumber = random(1);
        if (randNumber == 0){
          reverseRight(revSpeed, revDuration);
        }
        else{
          reverseLeft(revSpeed, revDuration);
        }
      }
      else if (edgeDetect == 1){
        reverseLeft(revSpeed, revDuration/1.5);
      }
      else if (edgeDetect == 2){
        reverseRight(revSpeed, revDuration);
      }
      else{
        forward(fwdSpeed);
      }
    }
  
    stop();
    break;
  }
}

void forward(int motorSpeed){
  digitalWrite(rightMotorDir, HIGH);
  analogWrite(rightMotorSpeed, motorSpeed);
  digitalWrite(leftMotorDir, LOW);  //right and left motor are mirror-mounted; neg. speed is forward for left motor
  analogWrite(leftMotorSpeed, motorSpeed);
}

void reverseRight(int motorSpeed, int revTime){
  //Both motors in reverse at different speeds
  digitalWrite(rightMotorDir, LOW);
  analogWrite(rightMotorSpeed, motorSpeed);
  digitalWrite(leftMotorDir, HIGH);  
  analogWrite(leftMotorSpeed, motorSpeed/2);  ////reverse at half the speed of right motor

  delay(revTime); //adjust for desired turn radius
}

void reverseLeft(int motorSpeed, int revTime){
  //Both motors in reverse at different speeds
  digitalWrite(rightMotorDir, LOW);
  analogWrite(rightMotorSpeed, motorSpeed/2); //reverse at half the speed of left motor
  digitalWrite(leftMotorDir, HIGH);  
  analogWrite(leftMotorSpeed, motorSpeed);

  delay(revTime); //adjust for desired turn radius
}

void reverse(int motorSpeed, int revTime){
  //Both motors in reverse at same speed
  digitalWrite(rightMotorDir, LOW);
  analogWrite(rightMotorSpeed, motorSpeed);
  digitalWrite(leftMotorDir, HIGH);
  analogWrite(leftMotorSpeed, motorSpeed);

  delay(revTime); //adjust for desired reverse distance
}

void stop(){
  analogWrite(rightMotorSpeed, 0);
  analogWrite(leftMotorSpeed, 0);
}
