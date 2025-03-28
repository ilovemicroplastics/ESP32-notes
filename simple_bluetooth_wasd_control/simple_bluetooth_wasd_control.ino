#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// {RB, LB, RF, LF} motor layout
const int PWM[] =   {18, 19, 21, 22};  // PWM pins
const int INP_1[] = {15, 4, 15, 4};    // Input 1 pins
const int INP_2[] = {16, 17, 16, 17};  // Input 2 pins

void setMotor(int dir, int PWMVal, int PWM, int INP_1, int INP_2) {
  // Motor control logic
  if (dir == 1) {
    digitalWrite(INP_1, LOW);
    digitalWrite(INP_2, HIGH);
  }
  else if (dir == -1) {
    digitalWrite(INP_1, HIGH);
    digitalWrite(INP_2, LOW);
  }
  else {
    digitalWrite(INP_1, LOW);
    digitalWrite(INP_2, LOW);
  }
  
  // Set motor speed
  ledcWrite(PWM, PWMVal);
}

void setup() {
  SerialBT.begin("ESP32_BT");

  // Initialize motor pins
  for(int k = 0; k < 4; k++){
    pinMode(PWM[k], OUTPUT);
    pinMode(INP_1[k], OUTPUT);
    pinMode(INP_2[k], OUTPUT);
    
    // Attach PWM channel to pin
    ledcAttach(PWM[k], 5000, 8);  // Pin, frequency, resolution

    delay(2000);
  }
}

void loop() {
  // Move all motors forward at full speed

  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    
    switch (incomingChar) {
        case 'w':
            // Move all motors forward
            for(int k = 0; k < 4; k++){
              setMotor(1, 255, PWM[k], INP_1[k], INP_2[k]);
            }
            break;
        case 'a':
            // Turn left: Left motors backward, Right motors forward
            // Left motors (RB, LB) move backward, Right motors (RF, LF) move forward
            setMotor(1, 255, PWM[0], INP_1[0], INP_2[0]); // RB
            setMotor(1, 150, PWM[1], INP_1[1], INP_2[1]); // LB  // reverse 
            setMotor(1, 255, PWM[2], INP_1[2], INP_2[2]);  // RF
            setMotor(1, 150, PWM[3], INP_1[3], INP_2[3]);  // LF // reverse
            break;
        case 'aa':
            // Turn left: Left motors backward, Right motors forward
            // Left motors (RB, LB) move backward, Right motors (RF, LF) move forward
            setMotor(1, 255, PWM[0], INP_1[0], INP_2[0]); // RB
            setMotor(-1, 255, PWM[1], INP_1[1], INP_2[1]); // LB  // reverse 
            setMotor(1, 255, PWM[2], INP_1[2], INP_2[2]);  // RF
            setMotor(-1, 255, PWM[3], INP_1[3], INP_2[3]);  // LF // reverse
            break;
        case 's':
            // Move all motors backward
            for(int k = 0; k < 4; k++){
              setMotor(-1, 255, PWM[k], INP_1[k], INP_2[k]);
            }
            break;
        case 'd':
            // Turn right: Left motors forward, Right motors backward
            // Left motors (RB, LB) move forward, Right motors (RF, LF) move backward
            setMotor(1, 150, PWM[0], INP_1[0], INP_2[0]); // RB  // reverse
            setMotor(1, 255, PWM[1], INP_1[1], INP_2[1]); // LB
            setMotor(1, 150, PWM[2], INP_1[2], INP_2[2]); // RF   // reverse
            setMotor(1, 255, PWM[3], INP_1[3], INP_2[3]); // LF
            break;
        case 'dd':
            // Turn right: Left motors forward, Right motors backward
            // Left motors (RB, LB) move forward, Right motors (RF, LF) move backward
            setMotor(-1, 255, PWM[0], INP_1[0], INP_2[0]); // RB  // reverse
            setMotor(1, 255, PWM[1], INP_1[1], INP_2[1]); // LB
            setMotor(-1, 255, PWM[2], INP_1[2], INP_2[2]); // RF   // reverse
            setMotor(1, 255, PWM[3], INP_1[3], INP_2[3]); // LF
            break;    
        default:
            delay(1500);
            // Stop all motors
            for(int k = 0; k < 4; k++){
              setMotor(0, 0, PWM[k], INP_1[k], INP_2[k]);
            }
            break;
    }
  }

  // Wait 
  delay(50);
}
