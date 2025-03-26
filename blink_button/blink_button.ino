// Define pin numbers
const int ledPin = 2;  // Built-in LED pin on most ESP32 boards
const int buttonPin = 4; // GPIO pin for the button

void setup() {
  pinMode(ledPin, OUTPUT);  // Set LED pin as output
  pinMode(buttonPin, INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { // Button pressed (active LOW)
    digitalWrite(ledPin, HIGH);  // Turn LED on
    delay(500);  // Wait for 500 milliseconds
    digitalWrite(ledPin, LOW);   // Turn LED off
    delay(500);  // Wait for 500 milliseconds
  }
}
