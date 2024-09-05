#include <ESP32Servo.h>

const int leftButtonPin = 21;
const int rightButtonPin = 22;

int leftLastState = HIGH;
int leftCurrentState;

int rightLastState = HIGH;
int rightCurrentState;

int ledPin = 27;
int rightLedPin = 26;

int servo1Pin = 17;
int servo2Pin = 16;
int servo1RD = 0;
int servo2RD = 0;

int flapSpeed;

Servo servo1;
Servo servo2;

void setup() {
  // LEDs
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);
  pinMode(rightLedPin, OUTPUT);

  servo1.attach(servo1Pin, 500, 2400);
  servo2.attach(servo2Pin, 500, 2400);
  servo1RD = 90;
  servo2RD = 90;
  servo1.write(servo1RD);
  servo2.write(servo2RD);

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
      if (servo1RD < 180) {
      servo1RD += flapSpeed; // Incrementa la rotación
      servo1.write(servo1RD);
      servo2.write(servo1RD);
      delay(20); // Ajusta la velocidad del servo

    }
  } else if (leftCurrentState == HIGH) {
    Serial.println("Botón 1 no presionado");
    digitalWrite(ledPin, LOW); // Apaga el LED
  }

  if (rightCurrentState == LOW) {
    Serial.println("Botón 2 presionado");
    digitalWrite(rightLedPin, HIGH);
  

      if (servo1RD > 0) {
      servo1RD -= flapSpeed; // Decrementa la rotación
      servo1.write(servo1RD);
      servo2.write(servo1RD);
      delay(20); // Ajusta la velocidad del servo

      }

  }

  else if (rightCurrentState = HIGH) {
    digitalWrite(rightLedPin, LOW);
  }


  leftLastState = leftCurrentState;
  rightLastState = rightCurrentState;

  delay(50); // Debounce delay
}


