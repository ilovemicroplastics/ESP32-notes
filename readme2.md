1️⃣ Hardware Connections

✅ Connect the ESP32s via UART:

    TX (Primary ESP32) → RX (Secondary ESP32)

    RX (Primary ESP32) ← TX (Secondary ESP32)

    Common Ground (GND to GND)

✅ Rewire Motor Control Pins to the Secondary ESP32

    The PWM and INP_1/INP_2 motor control pins should be moved from the Primary to the Secondary ESP32.

✅ Keep Encoder Inputs on the Primary ESP32

    The encoder signal wires (ENC_A & ENC_B) should still go to the Primary ESP32.

    
2️⃣ Modify the setMotor() Function

Since the motor control is now on the secondary ESP32, instead of directly setting pins, the Primary ESP32 should send motor commands via UART.
Original setMotor() function (Arduino Mega)

```
void setMotor(int dir, int PWMVal, int PWM, int INP_1, int INP_2){
  analogWrite(PWM, PWMVal);
  if(dir == 1){
    digitalWrite(INP_1, LOW);
    digitalWrite(INP_2, HIGH);
  }
  else if(dir == -1){
    digitalWrite(INP_1, HIGH);
    digitalWrite(INP_2, LOW);
  }
  else{
    digitalWrite(INP_1, LOW);
    digitalWrite(INP_2, LOW);
  }
}
```


3️⃣ Modify the Primary ESP32 Code (Send Motor Commands via UART)

Instead of directly controlling the motors, the Primary ESP32 should send commands over UART to the Secondary ESP32.
Modified setMotor() function (Primary ESP32)

```
void setMotor(int dir, int PWMVal, int motorID){
  Serial2.print(motorID); // Motor index
  Serial2.print(",");
  Serial2.print(dir);  // Direction: -1, 0, 1
  Serial2.print(",");
  Serial2.println(PWMVal); // PWM power level
}
```
💡 Use Serial2 for UART communication on ESP32 (TX: GPIO 17, RX: GPIO 16 by default).
💡 Example command sent: "0,1,150\n" (Motor 0, Forward, PWM 150)


4️⃣ Create Code for the Secondary ESP32 (Receive & Control Motors)

The Secondary ESP32 needs to listen for commands and set motor outputs.
Secondary ESP32 Code (Receives UART & Controls Motors)

```
void setup(){
  Serial2.begin(115200); // Start UART communication
  pinMode(8, OUTPUT); pinMode(9, OUTPUT);  // Example motor pins
  pinMode(22, OUTPUT); pinMode(23, OUTPUT);
}

void loop(){
  if (Serial2.available()) {
    String command = Serial2.readStringUntil('\n'); // Read UART message
    int motorID, dir, PWMVal;

    sscanf(command.c_str(), "%d,%d,%d", &motorID, &dir, &PWMVal); // Parse data

    // Replace these with actual motor control pins
    int PWM = (motorID == 0) ? 8 : 9;
    int INP_1 = (motorID == 0) ? 22 : 24;
    int INP_2 = (motorID == 0) ? 23 : 25;

    analogWrite(PWM, PWMVal);
    digitalWrite(INP_1, dir == 1 ? LOW : HIGH);
    digitalWrite(INP_2, dir == -1 ? HIGH : LOW);
  }
}
```
💡 This ESP32 reads the command from UART, extracts motor values, and sets the corresponding pins.


5️⃣ Final Steps

✔ Test communication between ESP32s (send simple messages first).
✔ Test motor control separately before integrating everything.
✔ Ensure a stable power supply for motors and ESP32s.


Final Summary

    Connect ESP32s via UART (TX → RX, RX → TX, GND shared).

    Move motor control pins to the Secondary ESP32.

    Modify setMotor() on Primary ESP32 to send UART commands instead of setting pins.

    Write a script on the Secondary ESP32 to receive UART messages and control motors.

    Test step by step before full integration.
