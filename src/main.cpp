#include <Arduino.h>
#include <Servo.h>

Servo servo0;  // Create a single servo object
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

void setup() {
  Serial.begin(9600);
  servo0.attach(2);
  servo1.attach(3);
  servo2.attach(4);
  servo3.attach(5);
  servo4.attach(6);
  servo5.attach(7);

  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);

}

void readAnalog(){
  int pot0 = analogRead(A0);
  int pot1 = analogRead(A1);
  int pot2 = analogRead(A2);
  int pot3 = analogRead(A3);
  int pot4 = analogRead(A4);
  int pot5 = analogRead(A5);

  Serial.print("pot0: ");
  Serial.print(pot0);
  Serial.print(" pot1: ");
  Serial.print(pot1);
  Serial.print(" pot2: ");
  Serial.print(pot2);
  Serial.print(" pot3: ");
  Serial.print(pot3);
  Serial.print(" pot4: ");
  Serial.print(pot4);
  Serial.print(" pot5: ");
  Serial.println(pot5);
}

void moveServos() {
  // Map potentiometer readings (0-1023) to servo angles (0-180)
  int servoPos0 = map(analogRead(A0), 0, 1023, 0, 360);
  int servoPos1 = map(analogRead(A1), 0, 1023, 0, 360);
  int servoPos2 = map(analogRead(A2), 0, 1023, 0, 360);
  int servoPos3 = map(analogRead(A3), 0, 1023, 0, 360);
  int servoPos4 = map(analogRead(A4), 0, 1023, 0, 360);
  int servoPos5 = map(analogRead(A5), 0, 1023, 0, 360);
  
  // Write positions to servos
  servo0.write(servoPos0);
  servo1.write(servoPos1);
  servo2.write(servoPos2);
  servo3.write(servoPos3);
  servo4.write(servoPos4);
  servo5.write(servoPos5);
}


void loop() {
  readAnalog();
  moveServos();
  delay(20); // Delay before next reading
}
