1️⃣ Hardware Connections

✅ Connect the ESP32s via UART:

    TX (Primary ESP32) → RX (Secondary ESP32)

    RX (Primary ESP32) ← TX (Secondary ESP32)

    Common Ground (GND to GND)

✅ Rewire Motor Control Pins to the Secondary ESP32

    The PWM and INP_1/INP_2 motor control pins should be moved from the Primary to the Secondary ESP32.

✅ Keep Encoder Inputs on the Primary ESP32

    The encoder signal wires (ENC_A & ENC_B) should still go to the Primary ESP32.

    
