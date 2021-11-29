#include <MeMegaPi.h>

MeMegaPiDCMotor motor1(PORT1B); //right motor
MeMegaPiDCMotor motor2(PORT2B); //left motor

int motorSpeed = 255;

void setup() {
  motor1.run(-motorSpeed);
  motor2.run(motorSpeed);
  delay(1000);
  motor1.stop();
  motor2.stop();
}

void loop() {

}
