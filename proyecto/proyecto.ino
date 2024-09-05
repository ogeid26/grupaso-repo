#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ESP32Servo.h>

// Botones

const int leftButtonPin = 34;
const int rightButtonPin = 35;

int leftLastState = HIGH;
int leftCurrentState;

int rightLastState = HIGH;
int rightCurrentState;

// LEDs

const int leftLedPin = 27;
const int rightLedPin = 26;

// Servo

// Left
const int servo1Pin = 16;
// Right
const int servo2Pin = 17;

int servo1RD;
int servo2RD;

int flapSpeed;

Servo servo1;
Servo servo2;

// Gyro
Adafruit_MPU6050 mpu;


void setup() {
  // LEDs
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  pinMode(leftLedPin, OUTPUT);
  pinMode(rightLedPin, OUTPUT);

  servo1.attach(servo1Pin, 500, 2400);
  servo2.attach(servo2Pin, 500, 2400);
  servo1RD = 90;
  servo2RD = 90;
  servo1.write(servo1RD);
  servo2.write(servo2RD);

  flapSpeed = 3;

  Serial.begin(115200);

  if (!mpu.begin()) {
     Serial.println("Sensor init failed");
     while (1)
    yield();
      }
}

void loop() {

  leftCurrentState = digitalRead(leftButtonPin);
  rightCurrentState = digitalRead(rightButtonPin);

  if (leftCurrentState == LOW) {
    Serial.println("Botón 1 presionado");
    digitalWrite(leftLedPin, HIGH); // Enciende el LED

    // Gira el servo mientras se presiona el botón
      if (servo1RD < 180) {
      servo1RD += flapSpeed; // Incrementa la rotación
      servo1.write(servo1RD);
      servo2.write(180-servo1RD);
      delay(20); // Ajusta la velocidad del servo

    }
  } else if (leftCurrentState == HIGH) {
//    Serial.println("Botón 1 no presionado");
    digitalWrite(leftLedPin, LOW); // Apaga el LED
  }

  if (rightCurrentState == LOW) {
    Serial.println("Botón 2 presionado");
    digitalWrite(rightLedPin, HIGH);
  

      if (servo1RD > 0) {
      servo1RD -= flapSpeed; // Decrementa la rotación
      servo1.write(servo1RD);
      servo2.write(180-servo1RD);
      delay(20); // Ajusta la velocidad del servo

      }

  }
    else if (rightCurrentState == HIGH) {
    digitalWrite(rightLedPin, LOW);
  }

  leftLastState = leftCurrentState;
  rightLastState = rightCurrentState;

  gyroInfo();
  delay(50); // Debounce delay

  
}

void gyroInfo() {
  sensors_event_t acc, gcc, temp;
mpu.getEvent(&acc, &gcc, &temp);
Serial.print("Acceleration on x axes: ");
Serial.println(acc.acceleration.x);
  delay(1000); // this speeds up the simulation

Serial.print("Acceleration on y axes: ");
Serial.println(acc.acceleration.y);
  delay(1000);

Serial.print("Acceleration on z axes: ");
Serial.println(acc.acceleration.z);
  delay(1000);

Serial.println("Rotation of x axes: ");
Serial.println((gcc.gyro.x)*180/3.14);
  delay(1000);

}


