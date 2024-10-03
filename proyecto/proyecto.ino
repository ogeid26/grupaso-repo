#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ESP32Servo.h>

// Servo Pins
const int servo1Pin = 16;
const int servo2Pin = 17;

int servo1RD = 90; // Initial position of servo1
int servo2RD = 90; // Initial position of servo2

const int neutralPosition = 90; // Neutral position for servos
const int flapSpeed = 6; // Speed of servo movement
const int returnSpeed = 1; // Speed of returning to neutral position

Servo servo1;
Servo servo2;
  
float rotationY;
float rotationX;

// Gyro
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting....");
  
  servo1.attach(servo1Pin, 500, 2400);
  servo2.attach(servo2Pin, 500, 2400);
  
  servo1.write(servo1RD);
  servo2.write(servo1RD);

  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1) {
      delay(10); // Wait here if sensor initialization fails
    }
  }
}

void loop() {
  sensors_event_t acc, gcc, temp;
  mpu.getEvent(&acc, &gcc, &temp);

  rotationY = gcc.gyro.y;
  rotationX = gcc.gyro.x;

  // Print values to Serial Plotter
  Serial.print("AccX:");
  Serial.println(acc.acceleration.x);
  
  Serial.print("AccY:");
  Serial.println(acc.acceleration.y);
  
  Serial.print("AccZ:");
  Serial.println(acc.acceleration.z);
  
  Serial.print("GyroX:");
  Serial.println(rotationX);
  
  Serial.print("GyroY:");
  Serial.println(rotationY);
  
  Serial.print("GyroZ:");
  Serial.println(gcc.gyro.z);

  // Control servos based on rotationY and rotationX
  if (abs(rotationX) > 0.5) { // Movement in X-axis, servos move in opposite directions
    if (rotationX > 0) {
      servo1RD += flapSpeed;  // Increase angle for servo1
      servo2RD += flapSpeed;  // Decrease angle for servo2
    } else {
      servo1RD -= flapSpeed;  // Decrease angle for servo1
      servo2RD -= flapSpeed;  // Increase angle for servo2
    }
  } else if (abs(rotationY) > 0.5) { // Movement in Y-axis, servos move in opposite directions
    if (rotationY > 0) {
      servo1RD += flapSpeed;  // Increase angle for servo1
      servo2RD -= flapSpeed;  // Decrease angle for servo2 (opposite)
    } else {
      servo1RD -= flapSpeed;  // Decrease angle for servo1
      servo2RD += flapSpeed;  // Increase angle for servo2 (opposite)
    }
  } else {
    // Gradually return to neutral position if no significant gyro movement
    if (servo1RD > neutralPosition) {
      servo1RD -= returnSpeed; // Move towards 90 degrees at returnSpeed
    } else if (servo1RD < neutralPosition) {
      servo1RD += returnSpeed; // Move towards 90 degrees at returnSpeed
    }
    
    if (servo2RD > neutralPosition) {
      servo2RD -= returnSpeed; 
    } else if (servo2RD < neutralPosition) {
      servo2RD += returnSpeed; 
    }
  }

  // Constrain to the valid range
  servo1RD = constrain(servo1RD, 0, 180);
  servo2RD = constrain(servo2RD, 0, 180);

  // Write new positions to servos
  servo1.write(servo1RD);
  servo2.write(servo2RD);

  delay(20); // Adjust delay for servo movement
}
