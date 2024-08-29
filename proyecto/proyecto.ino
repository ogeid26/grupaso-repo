#include <ESP32Servo.h>

const int leftButtonPin = 21;
const int rightButtonPin = 22;

int leftLastState = HIGH;
int leftCurrentState;

int rightLastState = HIGH;
int rightCurrentState;

int ledPin = 27;
int servoPin = 17;

Servo servo;
bool leftButtonPressed = false;

void setup() {
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);

  servo.attach(servoPin, 500, 2400);

  Serial.begin(115200);
}

void loop() {
  leftCurrentState = digitalRead(leftButtonPin);
  rightCurrentState = digitalRead(rightButtonPin);

  if (leftLastState == HIGH && leftCurrentState == LOW) {
    leftButtonPressed = !leftButtonPressed; // Toggle the button pressed state
    Serial.println("Botón 1 presionado");
  }

  if (leftButtonPressed) {
    digitalWrite(ledPin, HIGH); // Keep LED on
  } else {
    digitalWrite(ledPin, LOW); // Turn LED off
  }

  leftLastState = leftCurrentState;

  delay(50); // Debounce delay
}
