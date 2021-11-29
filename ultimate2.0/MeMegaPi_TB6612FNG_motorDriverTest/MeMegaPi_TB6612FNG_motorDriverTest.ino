/*
 * MeMegaPi_TB6612FNG_motorDriverTest
 * 
 * 
 */

void setup() {
  //digitalWrite(31, LOW);
  //digitalWrite(32, HIGH);
  //digitalWrite(33, HIGH);
  
  //Motor Carrier CA1
  digitalWrite(34, HIGH); //BINT2
  digitalWrite(35, LOW);  //BINT1
  
  //analogWrite(11, 255); //PWM for motor A 
  analogWrite(12, 255); //PWM for motor B

}

void loop() {
  // put your main code here, to run repeatedly:

}
