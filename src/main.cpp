#include <Arduino.h>
#include <Servo.h>

// Create Servo objects for four servos
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;

int servoPos[4];   // Array to store limited servo positions
int potValues[4];  // Array to store mapped potentiometer values

//pins definition
int servo[4] = {3, 5, 6, 9};
int Led[4] = {10, 8, 7, 4};
const int potRead[] = {A0, A1, A2, A3};

//home position and limits
int homepos[4] = {90,35, 95, 90};
int BOT_LIMIT[4] = {0, 0, 0, 0};
int TOP_LIMIT[4] = {180, 115, 180, 180};

void setup() {
  Serial.begin(9600);

  pinMode(Led[0], OUTPUT); //1. os
  pinMode(Led[1], OUTPUT); //2. os
  pinMode(Led[2], OUTPUT); //3. os
  pinMode(Led[3], OUTPUT); //4. os

  servo0.attach(servo[0]); //1. os
  servo1.attach(servo[1]); //2. os
  servo2.attach(servo[2]); //3. os
  servo3.attach(servo[3]); //4. os

  pinMode(A0, INPUT); //1. os
  pinMode(A1, INPUT); //2. os
  pinMode(A2, INPUT); //3. os
  pinMode(A3, INPUT); //4. os

  //Servo wake up sequence
  servo0.write(homepos[0]);
  delay(500); 
  servo1.write(homepos[1]);
  delay(500);
  servo2.write(homepos[2]);
  delay(500);
  servo3.write(homepos[3]);
  delay(500);

  //Potentiometer Home Calibration loop
  while (true){
    bool check[4] = {false, false, false, false};
    Serial.print("Set pot 90°: ");

    for (int i = 0; i < 4; i++) {//iterate for every motor, led, potentiometer

      int potValue = map(analogRead(potRead[i]),0,1023,0,180);  // Read once and store

      //DEBUG IN SERIAL
      Serial.print("Pot: ");
      Serial.print(homepos[i]);  // Add index number
      Serial.print("=");
      Serial.print(potValue);  // Add line break
      Serial.print("  ");
      
      if (potValue > homepos[i]-5 && potValue < homepos[i]+5) {
          check[i] = true;
          //Serial.println("Condition met!");

      }else{
          //Serial.println("Condition not met.");
          check[i] = false;
      }

      digitalWrite(Led[i], check[i]); //check calibration status and turn the led on/off
    }
    Serial.print("\n");
    
    if (check[0] && check[1] && check[2] && check[3]){
      break;
    }
  }  
}

//function to read potentiometers and move servos accordingly
void moveServos() {
  // Map potentiometer readings (0-1023) to servo angles (0-180)
  for (int i = 0; i < 4; i++) {
    servoPos[i] = map(analogRead(potRead[i]), 0, 1023, BOT_LIMIT[i], TOP_LIMIT[i]);
    
    Serial.print(servoPos[i]); Serial.print(" ");
    if (i == 3) Serial.println();
  }

  //CHECK SERVO COLISIONS
  // int L3 = 180-servoPos[3]-90; //L3 = 90 - servo3
  // int L2 = servoPos[2]+50;     //L2 = servo2 - 90
  // int Lim = L2-L3;
  // Serial.print("Lim: "); Serial.print(Lim);
  // Serial.print(", L2 = "); Serial.print(L2);
  // Serial.print(", L3 = "); Serial.println(L3);
  
  // Write positions to servos using array
  
  servo0.write(servoPos[0]);

  servo1.write(servoPos[1]); 

  servo2.write(servoPos[2]);

  servo3.write(servoPos[3]); 
}


void loop() {
  moveServos();
  delay(20); // Delay before next reading
}
