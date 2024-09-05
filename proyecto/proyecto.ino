#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ESP32Servo.h>

// Servo Pins
const int servo1Pin = 16;
const int servo2Pin = 17;

int servo1RD = 90; // Initial position of servo1
int servo2RD = 90; // Initial position of servo2
int random_variable;


const int flapSpeed = 6; // Speed of servo movement

Servo servo1;
Servo servo2;

float rotationY;

// Gyro
Adafruit_MPU6050 mpu;

void setup() {
  servo1.attach(servo1Pin, 500, 2400);
  servo2.attach(servo2Pin, 500, 2400);
  
  servo1.write(servo1RD);
  servo2.write(servo2RD);

  Serial.begin(115200);

  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1) {
      delay(10); // Wait here if sensor initialization fails
    }
  }
}

void loop() {
    random_variable = random(0, 1000);
  sensors_event_t acc, gcc, temp;
  mpu.getEvent(&acc, &gcc, &temp);

  rotationY = gcc.gyro.y;

  Serial.print("Variable_1:");
  Serial.print(random_variable);
  Serial.print(",");

  // Print values to Serial Plotter
  Serial.print("AccX:");
  Serial.print(acc.acceleration.x);
  Serial.print(",");

  Serial.print("AccY: ");
  Serial.print(acc.acceleration.y);
  Serial.print(",");

  Serial.print("AccZ: ");
  Serial.print(acc.acceleration.z);
  Serial.print(",");

  Serial.print("GyroX: ");
  Serial.print(gcc.gyro.x);
  Serial.print(",");

  Serial.print("GyroY: ");
  Serial.print(rotationY);
  Serial.print(",");

  Serial.print("GyroZ: ");
  Serial.println(gcc.gyro.z);
  Serial.print(",");


  // Control servos based on rotationY
  if (abs(rotationY) > 1.0) { // Adjust the threshold as needed
    if (rotationY > 0) {
      if (servo1RD < 180) {
        servo1RD += flapSpeed;
        servo1.write(servo1RD);
        //servo2RD = 180 - servo1RD;
        servo2.write(servo1RD);
      }
    } else {
      if (servo1RD > 0) {
        servo1RD -= flapSpeed;
        servo1.write(servo1RD);
       // servo2RD = 180 - servo1RD;
        servo2.write(servo1RD);
      }
    }
    delay(20); // Adjust delay for servo movement
  }

  delay(50); // Debounce delay
}
