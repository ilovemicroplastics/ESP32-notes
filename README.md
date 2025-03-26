Start by downloading ArduinoIDE.

2.0
<https://www.arduino.cc/en/Main/Software>

add Library
esp32 by Espressif Systems

Test program.
```
#include <Arduino.h>

#define LED 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  Serial.println("LED is on");
  delay(1000);
  digitalWrite(LED, LOW);
  Serial.println("LED is off");
  delay(1000);
}
```

Get drivers:
<https://randomnerdtutorials.com/install-esp32-esp8266-usb-drivers-cp210x-windows/>
<https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads>
