#include <IRremote.h>

const int RECV_PIN = 7;
const int greenled = 11;
const int yellowled = 12;
const int redled = 13;
const int buzzpin = 9;

uint8_t lastCommand = 0; // To store last valid command

void setup() {
  pinMode(greenled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(buzzpin, OUTPUT);
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver Ready. Point your remote...");
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t irValue = IrReceiver.decodedIRData.command;

    // Ignore repeat code (sent when button is held)
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
      irValue = lastCommand; // Reuse last valid command
    } else {
      lastCommand = irValue; // Store new valid command
    }

    Serial.print("IR Code: 0x");
    Serial.println(irValue, HEX);

    switch (irValue) {
      case 0x1:
        Serial.println("Number 1 pressed, turning on green LED");
        digitalWrite(greenled, HIGH);
        digitalWrite(yellowled, LOW);
        digitalWrite(redled, LOW);
        break;

      case 0x2:
        Serial.println("Number 2 pressed, turning on yellow LED");
        digitalWrite(yellowled, HIGH);
        digitalWrite(greenled, LOW);
        digitalWrite(redled, LOW);
        break;

      case 0x45:
        Serial.println("Power button pressed!");
        break;

      case 0x46:
        Serial.println("Volume up!");
        break;

      case 0x47:
        Serial.println("Volume down!");
        break;

      default:
        Serial.println("Unknown button");
        digitalWrite(yellowled, LOW);
        digitalWrite(greenled, LOW);

        // Flash red LED and buzz 3 times
        for (int i = 0; i < 3; i++) {
          digitalWrite(redled, HIGH);
          tone(buzzpin, 1600, 500);
          delay(500);
          digitalWrite(redled, LOW);
          delay(500);
        }
        break;
    }

    IrReceiver.resume();
  }
}



