#include <ESP32Servo.h>

const int leftButtonPin = 21;
const int rightButtonPin = 22;

int leftLastState = HIGH;
int leftCurrentState;

int rightLastState = HIGH;
int rightCurrentState;

int ledPin = 27;
int servoPin = 17;
int rotationDegree = 0;

int flapSpeed;

Servo servo;

void setup() {
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);

  servo.attach(servoPin, 500, 2400);
  rotationDegree = 90;
  servo.write(rotationDegree);

  flapSpeed = 3;

  Serial.begin(115200);
}

void loop() {
  leftCurrentState = digitalRead(leftButtonPin);
  rightCurrentState = digitalRead(rightButtonPin);

  if (leftCurrentState == LOW) {
    Serial.println("Botón 1 presionado");
    digitalWrite(ledPin, HIGH); // Enciende el LED

    // Gira el servo mientras se presiona el botón
      if (rotationDegree < 180) {
      rotationDegree += flapSpeed; // Incrementa la rotación
      servo.write(rotationDegree);
      delay(15); // Ajusta la velocidad del servo
    }
  } else {
    Serial.println("Botón 1 no presionado");
    digitalWrite(ledPin, LOW); // Apaga el LED
  }

  leftLastState = leftCurrentState;

  delay(50); // Debounce delay
}
