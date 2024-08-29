#include <ESP32Servo.h>

const int leftButtonPin = 21;
const int rightButtonPin = 22;

const int servoPin = 18;

int leftLastState = HIGH;
int leftCurrentState;

int rightLastState = HIGH;
int rightCurrentState;

Servo myServo;

void setup() {
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  Serial.begin(115200);
}

void loop() {

  leftCurrentState = digitalRead(leftButtonPin);
  rightCurrentState = digitalRead(rightButtonPin);


  if (leftLastState == LOW && leftCurrentState == HIGH) {
    Serial.println("Botón 1 presionado");
  } else {
    Serial.println("Botón 1 no presionado");
  }
  leftLastState = leftCurrentState;
  delay(200);
}
