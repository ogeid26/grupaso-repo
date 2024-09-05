#include "ButtonHandler.h"
#include "ServoHandler.h"
#include <Arduino.h>

 int leftButtonPin = 21;
 int rightButtonPin = 22;
 int ledPin = 27;
 int rightLedPin = 26;

int leftCurrentState;
int rightCurrentState;

void setupButtons() {
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(rightLedPin, OUTPUT);
}

void handleLeftButton() {
  leftCurrentState = digitalRead(leftButtonPin);

  if (leftCurrentState == LOW) {
    Serial.println("Botón 1 presionado");
    digitalWrite(ledPin, HIGH);  // Turn on LED
    incrementServo();            // Move servo 1
    delay(20);
  } else {
    digitalWrite(ledPin, LOW);   // Turn off LED
  }
}

void handleRightButton() {
  rightCurrentState = digitalRead(rightButtonPin);

  if (rightCurrentState == LOW) {
    Serial.println("Botón 2 presionado");
    digitalWrite(rightLedPin, HIGH); // Turn on LED
    decrementServo();               // Move servo 2
    delay(20);
  } else {
    digitalWrite(rightLedPin, LOW);  // Turn off LED
  }
}
