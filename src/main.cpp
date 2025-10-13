#include <Arduino.h>
#include <Servo.h>

Servo servo0;  // Create a single servo object
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int servoPos[6];   // Array to store servo positions
int potValues[6];

const int potRead[] = {A0, A1, A2, A3, A4, A5};
int homepos[6] = {90, 90, 0, 90, 90, 90};
int BOT_LIMIT[6] = {0, 0, 0, 0, 90, 0};
int TOP_LIMIT[6] = {180, 180, 120, 120, 150, 180};

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

  while (true){
    bool check[6] = {false, false, false, false, false, false};

    Serial.print("Set pot 90°: ");

    for (int i = 0; i < 6; i++) {
      int potValue = map(analogRead(potRead[i]),0,1023,0,180);  // Read once and store
      
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
    }
    Serial.print("\n");
    
    if (check[0] && check[1] && check[2] && check[3] && check[4] && check[5]){
      break;
    }
  }  
}

void moveServos() {
  // Map potentiometer readings (0-1023) to servo angles (0-180)
  for (int i = 0; i < 6; i++) {
    servoPos[i] = map(analogRead(potRead[i]), 0, 1023, BOT_LIMIT[i], TOP_LIMIT[i]);
    
    Serial.print(servoPos[i]); Serial.print(" ");
    if (i == 5) Serial.println();
  }

  //CHECK SERVO COLISIONS
  int L3 = 180-servoPos[3]-90; //L3 = 90 - servo3
  int L2 = servoPos[2]+50;     //L2 = servo2 - 90
  int Lim = L2-L3;
  // Serial.print("Lim: "); Serial.print(Lim);
  // Serial.print(", L2 = "); Serial.print(L2);
  // Serial.print(", L3 = "); Serial.println(L3);
  
  // Write positions to servos using array
  servo0.write(servoPos[0]);
  servo1.write(servoPos[1]);
  
  servo2.write(servoPos[2]); //DEF 0, 0-120
  if(Lim<23){
    servo3.write(113-L2); //DEF 90, 0-120
  }else{
    servo3.write(servoPos[3]); //DEF 90, 0-120
  }
  servo4.write(servoPos[4]); //DEF 90, 90-140
  servo5.write(servoPos[5]); //DEF 90, 0-180

}


void loop() {
  moveServos();
  delay(20); // Delay before next reading
}
